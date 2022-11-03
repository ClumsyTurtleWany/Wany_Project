#include "FBXLoader.hpp"

bool FBXLoader::initialize()
{
	m_pManager = FbxManager::Create(); // static���� ���� ��.
	if (m_pManager != nullptr)
	{
		m_pImporter = FbxImporter::Create(m_pManager, ""); // �����ڵ� ��� ����. static���� ���� ��.
		if (m_pImporter == nullptr)
		{
			OutputDebugString(L"WanyCore::FBXLoader::initialize::Failed Create Fbx Importer.\n");
			return false;
		}

		return true;
	}
	else
	{
		OutputDebugString(L"WanyCore::FBXLoader::initialize::Failed Create Fbx Manager.\n");
		return false;
	}
}

bool FBXLoader::frame()
{
	return true;
}

bool FBXLoader::render()
{
	return true;
}

bool FBXLoader::release()
{
	m_ObjectMap.clear();

	if (m_pImporter != nullptr)
	{
		m_pImporter->Destroy();
		m_pImporter = nullptr;
	}
	
	if (m_pManager != nullptr)
	{
		m_pManager->Destroy();
		m_pManager = nullptr;
	}

	return true;
}

bool FBXLoader::LoadDir(std::wstring _path)
{
	setResourceDirectory(_path);
	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filename = file.path().filename();
		std::wstring filepath = file.path();
		std::wstring fileExtension = file.path().extension();

		if (fileExtension == L"")
		{
			std::wstring dir = filepath + L"/";
			LoadDir(dir);
		}
		else
		{
			if ((fileExtension == L".FBX") || (fileExtension == L".fbx"))
			{
				if (filename == L"Turret_Deploy1.FBX")
				{
					int a = 0;
				}

				auto it = m_ObjectMap.find(filename);
				if (it != m_ObjectMap.end())
				{
					continue;
				}

				std::unique_ptr<FBXObject> Object = std::make_unique<FBXObject>();
				if (Load(filepath, Object.get()))
				{
					m_ObjectMap.insert(std::make_pair(filename, std::move(Object)));
				}
			}
			else
			{
				continue;
			}
		}
	}

	return true;
}

bool FBXLoader::Load(std::wstring _path, FBXObject* _dst)
{
	std::string strPath;
	strPath.assign(_path.begin(), _path.end());
	const char* path = strPath.c_str();

	if (!m_pImporter->Initialize(path))
	{
		OutputDebugString(L"WanyCore::FBXLoader::Load::Failed Initialize Importer.\n");
		return false;
	}

	// �⺻������ ������ ���ϵ��� Scene ������ �����.
	// Scene�� Ʈ�� ������ �̷���� �־� Root���� ���۵Ǹ� ���� Root�� NULL�� �̷��������.
	// ���� ���� ���� ���� �����ؼ� �ε� ���� �ʿ䰡 ����.
	FbxScene* pScene = FbxScene::Create(m_pManager, "");
	if (pScene == nullptr)
	{
		OutputDebugString(L"WanyCore::FBXLoader::Load::Failed Create Scene.\n");
		return false;
	}

	// �� FBX�� ����� ��(3D Max, ���� �� ������ ��)���� ���� ��� ������ �ٸ� �� �ֱ� ������ ���� �� �ε� �� �� �ִ�.
	// ������ FBX�� �⺻������ ������ ��ǥ��, Y-Up
	FbxSystemUnit::cm.ConvertScene(pScene); // ���� ����. cm ������ ����
	//FbxAxisSystem::MayaZUp.ConvertScene(pScene); // ���� �� ����. ���� �������� ����. ���� ��ȯ�� �ƴ� ��Ŀ� ���� �Ǵ� ����.
	FbxAxisSystem sceneAxisSystem = pScene->GetGlobalSettings().GetAxisSystem();
	FbxAxisSystem::DirectX.ConvertScene(pScene); // ���� �� ����. DirectX �������� �ٲ㵵 ���� �츮�� ����ϴ� ��� �ٸ�. (Right Vector�� ���̳ʽ���.).
	FbxAxisSystem sceneAxisSystemAfter = pScene->GetGlobalSettings().GetAxisSystem();

	if (!m_pImporter->Import(pScene))
	{
		OutputDebugString(L"WanyCore::FBXLoader::Load::Failed Import Scene.\n");
		return false;
	}

	FbxNode* pRoot = pScene->GetRootNode();
	if (!ParseNode(pRoot, _dst))
	{
		OutputDebugString(L"WanyCore::FBXLoader::Load::Failed Parse Root Node.\n");
		return false;
	}

	pRoot->Destroy();
	pScene->Destroy();

	return true;
}

bool FBXLoader::ParseNode(FbxNode* _node, FBXObject* _dst)
{
	if ((_node == nullptr) || (_dst == nullptr))
	{
		OutputDebugString(L"WanyCore::FBXLoader::ParseNode::Node or Dest is nullptr.\n");
		return false;
	}

	bool isValid = false;
	FbxNodeAttribute* pAttribute = _node->GetNodeAttribute();
	if (pAttribute != nullptr)
	{
		// Attribute Type
		// eUnknown,
		// eNull, // ���� ������Ʈ�� �̿� �� ���� ����.
		// eMarker,
		// eSkeleton, // �ִϸ��̼ǿ� ������.
		// eMesh, // �������� ������.
		// eNurbs,
		// ePatch,
		// eCamera,
		// eCameraStereo,
		// eCameraSwitcher,
		// eLight,
		// eOpticalReference,
		// eOpticalMarker,
		// eNurbsCurve,
		// eTrimNurbsSurface,
		// eBoundary,
		// eNurbsSurface,
		// eShape,
		// eLODGroup,
		// eSubDiv,
		// eCachedEffect,
		// eLine

		FbxNodeAttribute::EType attributeType = pAttribute->GetAttributeType();
		switch (attributeType)
		{
			case FbxNodeAttribute::EType::eNull: // ���� Root ���� NULL�� ����.
			{
				isValid = true;
				FbxNull* pDummy = _node->GetNull();
				if (pDummy != nullptr)
				{
					// Dummy: �ڽ� ������Ʈ�� ������ �θ� ������Ʈ�� ������ �����ֱ� ���� ����.
					ParseDummy(pDummy, _dst);
				}
				break;
			}

			case FbxNodeAttribute::EType::eSkeleton:
			{
				isValid = true;
				FbxSkeleton* pSkeleton = _node->GetSkeleton();
				if (pSkeleton != nullptr)
				{
					// Skeleton: �ִϸ��̼��� ���� ����
					ParseSkeleton(pSkeleton, _dst);
				}
				break;
			}

			case FbxNodeAttribute::EType::eMesh:
			{
				isValid = true;
				FbxMesh* pMesh = _node->GetMesh();
				if (pMesh != nullptr)
				{
					// Mesh: ���� ������ ������
					// Scene graph ����(Ʈ���� ��� ������ �� �־ ���� �� ��� �� �������ϴ� ���) �̶�� �θ�.
					ParseMesh(pMesh, _dst);
				}
				break;
			}
		}
	}

	_dst->m_strNodeName = _node->GetName();

	int childCount = _node->GetChildCount(); // Child ������ 0�̸� ���� �Ž�, 0�� �ƴϸ� ���� �Ž��� �� �� ����.
	for (int idx = 0; idx < childCount; idx++)
	{
		FBXObject* childObject = new FBXObject;
		FbxNode* pChild = _node->GetChild(idx);
		if (ParseNode(pChild, childObject))
		{
			_dst->child.push_back(childObject);
		}
		else
		{
			delete childObject;
		}
	}
	
	return isValid;
}

bool FBXLoader::ParseMesh(FbxMesh* _mesh, FBXObject* _dst)
{
	if ((_mesh == nullptr) || (_dst == nullptr))
	{
		return false;
	}

	_dst->m_strDataName = _mesh->GetName();
	_dst->m_wstrNodeType = L"Mesh";

	int DeformerCnt = _mesh->GetDeformerCount();
	for (int idx = 0; idx < DeformerCnt; idx++)
	{
		FbxDeformer* pDeformer = _mesh->GetDeformer(idx, FbxDeformer::EDeformerType::eSkin);
		FbxSkin* pSkin = reinterpret_cast<FbxSkin*>(pDeformer);
		int ClusterCnt = pSkin->GetClusterCount();
		for (int clusterIdx = 0; clusterIdx < ClusterCnt; clusterIdx++)
		{
			FbxCluster* pCluster = pSkin->GetCluster(clusterIdx);
			int clusterSize = pCluster->GetControlPointIndicesCount();

			FbxNode* pLinkNode = pCluster->GetLink();
			std::string LinkedNodeName = pLinkNode->GetName();

			int* indices = pCluster->GetControlPointIndices();
			int a = 0;
			
		}
		
	}

	// Layer ���� �ʿ�. �������� ���� ������ ���� ������ �ϴ°� == ��Ƽ �н� ������. �ؽ��ķ� ġȯ�ϸ� ��Ƽ �ؽ�ó ������.
	std::vector<FbxLayerElementUV*> UVList;
	std::vector<FbxLayerElementVertexColor*> ColorList;
	std::vector<FbxLayerElementMaterial*> MaterialList;
	std::vector<FbxLayerElementNormal*> NormalList;
	
	int layerCount = _mesh->GetLayerCount();
	for (int layerIdx = 0; layerIdx < layerCount; layerIdx++)
	{
		FbxLayer* pLayer = _mesh->GetLayer(layerIdx);
		FbxLayerElementUV* pUV = pLayer->GetUVs();
		if (pUV != nullptr)
		{
			UVList.push_back(pUV);
		}

		FbxLayerElementVertexColor* pColor = pLayer->GetVertexColors();
		if (pColor != nullptr)
		{
			ColorList.push_back(pColor);
		}

		FbxLayerElementMaterial* pMaterial = pLayer->GetMaterials();
		if (pMaterial != nullptr)
		{
			MaterialList.push_back(pMaterial);
		}

		FbxLayerElementNormal* pNormal = pLayer->GetNormals();
		if (pNormal != nullptr)
		{
			NormalList.push_back(pNormal);
		}
	}

	FbxNode* pNode = _mesh->GetNode(); // ������ Mesh�� �ƴ� Node�� �����°� �´�.  
	// �� ���̽� ���� �ٸ� �ؽ��ĸ� ��� �� �� �ִ�. �̰��� ���� ���׸��� �̶�� ��. (1���� ������Ʈ�� �������� �ؽ��� ���)
	// ���� ���׸����� ������ �ϱ� ���ؼ� ���� �ؽ��ĸ� ����ϴ� ���̽����� ��� ���.
	int MaterialCnt = pNode->GetMaterialCount(); // �ؽ��İ� ���� ����.
	std::vector<std::vector<Vertex>> VertexList;
	if (MaterialCnt == 0)
	{
		VertexList.resize(1);
		_dst->Materials.resize(1);
		if (DXShaderManager::getInstance()->Load(objectCnt, ShaderType::Object3D))
		{
			_dst->Materials[0] = DXShaderManager::getInstance()->getShader(objectCnt++);
		}
	}
	else
	{
		VertexList.resize(MaterialCnt);
		_dst->Materials.resize(MaterialCnt);
		for (size_t idx = 0; idx < MaterialCnt; idx++)
		{
			if (DXShaderManager::getInstance()->Load(objectCnt, ShaderType::Object3D))
			{
				_dst->Materials[idx] = DXShaderManager::getInstance()->getShader(objectCnt++);
			}
		}
	}

	std::string textureName;
	for (int idx = 0; idx < MaterialCnt; idx++)
	{
		// �ؽ�ó ������ �������� ���� ��. ���� 1���� Surface�� 24�� �̻��� �ؽ��İ� �پ� �ִ�.(24�� �̻��� �ؽ��� ����� �����Ѵ�.)
		// �ؽ��� ���� ������ �ִ�(ex. ����ũ �ؽ�óó�� ���ĸ� ���� ��� �� �������� ������ ����.)
		FbxSurfaceMaterial* pSurface = pNode->GetMaterial(idx);
		if (pSurface != nullptr)
		{
			std::wstring filename;
			DXTexture* pTexture = FindTexture(pSurface, FbxSurfaceMaterial::sDiffuse, &filename);
			if (pTexture != nullptr)
			{
				_dst->Materials[idx]->setTexture(pTexture);
			}

			if (!filename.empty())
			{
				_dst->Materials[idx]->setTextureFile(filename);
			}

			std::wstring filename2;
			DXTexture* pTexture2 = FindTexture(pSurface, FbxSurfaceMaterial::sAmbient, &filename2);
			if (pTexture2 != nullptr)
			{
				_dst->Materials[idx]->setTexture(pTexture2);
			}

			if (!filename2.empty())
			{
				_dst->Materials[idx]->setTextureFile(filename2);
			}
		}
	}


	// ���� ���
	// Affine ����� ���� ��ȯ �� ��, �׳� ����� ��� ���� ���� �� �� ���
	FbxAMatrix geometryMatrix = getGeometryMatrix(pNode); // ���� ���. �ʱ� ���� ��ġ�� ��ȯ �� �� ���. ���� ���. �� ��Ʈ������ ������ �ٲ��� ������ ���� ��Ŀ��� ��ȯ. ���� ��ȯ.

	// �븻 ������ ������� ��ġ ��ķ� ���� ��� ��.
	FbxAMatrix normalMatrix = getNormalMatrix(geometryMatrix);

	// ���� ���, �ִϸ��̼ǿ��� ��� �ϸ� �ȵ�. ������ �ۿ��� ����ؾ� �ϳ� �ӽ÷� ���
	FbxAMatrix worldMatrix = getWorldMatrix(pNode);
	FbxAMatrix normalMatrix_World = getNormalMatrix(worldMatrix);


	int polyCount = _mesh->GetPolygonCount();
	// 3���� = 1������(Triangle) �� ���� �ְ�
	// 4���� = 1������(Quad) �� ���� �ִ�.
	// ������ -> ���̽� -> ����
	int basePolyIdx = 0; // Color
	int MaterialIdx = 0;
	for (int polyIdx = 0; polyIdx < polyCount; polyIdx++)
	{
		int polySize = _mesh->GetPolygonSize(polyIdx);
		int faceCount = polySize - 2;
		if (!MaterialList.empty())
		{
			MaterialIdx = getSubMaterialIndex(MaterialList[0], polyIdx);
		}

		FbxVector4* pVertexPosition = _mesh->GetControlPoints(); // ������(Control point == Vertices). ������ ���� ��ġ. 
		for (int faceIdx = 0; faceIdx < faceCount; faceIdx++)
		{
			// FBX�� �ð� �ݴ� ������. DirectX�� ��ǥ�� ������ �ٸ���. 
			// Max ��ǥ�� Y���� Z��, Z���� Y��, (DX.x == Max.x, DX.y = Max.z, DX.z = Max.y)
			// DX ���� 		Max ����
			// 1 0 0 0		1 0 0 0
			// 0 1 0 0		0 0 1 0
			// 0 0 1 0		0 1 0 0
			// 0 0 0 1		0 0 0 1
			////////////////////////////
			// Texture
			// DX			Max
			// (0,0) (1,0)  (0,1) (1,1)
			// 
			// (0,1) (1,1)  (0,0) (1,0)
			/////////////////////////////
			int cornerIdx[3];
			cornerIdx[0] = _mesh->GetPolygonVertex(polyIdx, 0);
			cornerIdx[1] = _mesh->GetPolygonVertex(polyIdx, faceIdx + 2);
			cornerIdx[2] = _mesh->GetPolygonVertex(polyIdx, faceIdx + 1);

			int UVidx[3] = { 0, };
			UVidx[0] = _mesh->GetTextureUVIndex(polyIdx, 0);
			UVidx[1] = _mesh->GetTextureUVIndex(polyIdx, faceIdx + 2);
			UVidx[2] = _mesh->GetTextureUVIndex(polyIdx, faceIdx + 1);

			int vertexColorIdx[3] = { 0, faceIdx + 2, faceIdx + 1 };
			for (int idx = 0; idx < 3; idx++)
			{
				int vertexIdx = cornerIdx[idx];
				FbxVector4 vertex = pVertexPosition[vertexIdx];
				vertex = geometryMatrix.MultT(vertex); // ���� ��� ��ȯ, Transform�� T, �� �켱 ���
				vertex = worldMatrix.MultT(vertex); // ���� ��ȯ ���. ���߿� �� ��.

				Vector3f pos;
				pos.x = vertex.mData[0];
				pos.y = vertex.mData[2];
				pos.z = vertex.mData[1];

				Vector3f normal;
				Vector4f color = { 1.0f, 1.0f, 1.0f, 1.0f };
				Vector2f texture;
				FbxVector2 tex; // = ;
				int uvidx = UVidx[idx];
				if (!UVList.empty())
				{
					if (ReadTextureCoord(UVList[0], vertexIdx, uvidx, tex))
					{
						texture.x = tex.mData[0];
						texture.y = 1.0f - tex.mData[1];
					}
				}

				if (!ColorList.empty())
				{
					int colorIdx = basePolyIdx + vertexColorIdx[idx];
					FbxColor fbxColor;
					if (ReadColorCoord(ColorList[0], vertexIdx, colorIdx, fbxColor))
					{
						color.x = fbxColor.mRed;
						color.y = fbxColor.mGreen;
						color.z = fbxColor.mBlue;
						//color.w = fbxColor.mAlpha;
						color.w = 1.0f;
					}
				}

				if (!NormalList.empty())
				{
					int normalIdx = basePolyIdx + vertexColorIdx[idx];
					FbxVector4 fbxNormal;
					if (ReadNormal(NormalList[0], vertexIdx, normalIdx, fbxNormal))
					{
						fbxNormal = normalMatrix.MultT(fbxNormal);
						fbxNormal = normalMatrix_World.MultT(fbxNormal); // ���� ��ȯ. ���߿� �� ��.
						normal.x = fbxNormal.mData[0];
						normal.y = fbxNormal.mData[2];
						normal.z = fbxNormal.mData[1];
					}
				}

				VertexList[MaterialIdx].push_back(Vertex(pos, normal, color, texture));
			}


		}

		basePolyIdx += polySize;
	}

	for (size_t idx = 0; idx < _dst->Materials.size(); idx++)
	{
		_dst->Materials[idx]->updateVertexList(&VertexList[idx]);
		std::vector<DWORD> indexList;
		for (size_t idx2 = 0; idx2 < VertexList[idx].size(); idx2++)
		{
			indexList.push_back(idx2);
		}
		_dst->Materials[idx]->updateIndexList(&indexList);
	}

	return true;
}

bool FBXLoader::ParseDummy(FbxNull* _dummy, FBXObject* _dst)
{
	if ((_dummy == nullptr) || (_dst == nullptr))
	{
		return false;
	}

	_dst->m_strDataName = _dummy->GetName();
	_dst->m_wstrNodeType = L"Null";
	return true;
}

bool FBXLoader::ParseSkeleton(FbxSkeleton* _skeleton, FBXObject* _dst)
{
	if ((_skeleton == nullptr) || (_dst == nullptr))
	{
		return false;
	}

	_dst->m_strDataName = _skeleton->GetName();

	int DstObjectCnt = _skeleton->GetDstObjectCount();
	for (int i = 0; i < DstObjectCnt; i++)
	{
		FbxObject* pObject = _skeleton->GetDstObject(i);
		if (pObject != nullptr)
		{
			_dst->m_strTargetName.push_back(pObject->GetName());
		}
	}

	int SrcObjectCnt = _skeleton->GetSrcObjectCount();
	for (int i = 0; i < SrcObjectCnt; i++)
	{
		FbxObject* pObject = _skeleton->GetSrcObject(i);
		if (pObject != nullptr)
		{
			_dst->m_strTargetName.push_back(pObject->GetName());
		}
	}

	FbxSkeleton::EType skeletonType = _skeleton->GetSkeletonType();
	FbxColor skeletonColor = _skeleton->GetLimbNodeColor();
	double limbNodeSize = _skeleton->GetLimbNodeSizeDefaultValue();
	
	_dst->m_wstrNodeType = L"Skeleton";
	return true;
}

bool FBXLoader::ReadTextureCoord(FbxLayerElementUV* _uv, int _vertexIdx, int _uvIdx, FbxVector2& _dst)
{
	if (_uv == nullptr || _dst == nullptr)
	{
		return false;
	}

	// �ؽ�ó ���� ����� �������� ����.
	// EMappingMode
	// eNone: ������ �������� �ʾҴ�.
	// eByControlPoint: ���������� 1���� ������ �Ǿ� �ִ�. (�� ������ UV��ǥ�� ��� ����.)
	// eByPolygonVertex: �� ������ ���� �����￡ ���ο� ��ǥ�� �ִ�. (�����￡�� Ž�� �ؾ���)
	// eByPolygon: ��ü �����￡ ���� ��ǥ�� �ִ�. 
	// eByEdge: ������ 1���� ���� ��ǥ�� �ִ�.
	// eAllSame: ��ü �����￡ 1���� ���� ��ǥ�� �ִ�.
	// ���� ��� -> ���� ��� Ȯ�� �ʿ�. == Reference Mode
	// eDirect: ����Ʈ�� ����Ǿ� ����. N��° ���� ������ DirectArray�� N��° ��ġ�� �ִ�.
	// eIndex: FBX 5.0 ���� �������� ���Ǿ���. ������ ������� ����. �� �̻��� ���������� eIndexToDirect�� ��ü��.
	// eIndexToDirect: �ε����� ����Ǿ� ����. 
	switch (_uv->GetMappingMode())
	{
		case FbxLayerElementUV::eByControlPoint:
		{
			// ���� ���� UV�� 1���� ������ �ش� Vertex���� ������ ������.
			switch (_uv->GetReferenceMode())
			{
				case FbxLayerElementUV::eDirect:
				{
					FbxVector2 fbxUv = _uv->GetDirectArray().GetAt(_vertexIdx); 
					_dst.mData[0] = fbxUv.mData[0];
					_dst.mData[1] = fbxUv.mData[1];
					break;
				}
				case FbxLayerElementUV::eIndexToDirect:
				{
					int id = _uv->GetIndexArray().GetAt(_vertexIdx);
					FbxVector2 fbxUv = _uv->GetDirectArray().GetAt(id);
					_dst.mData[0] = fbxUv.mData[0];
					_dst.mData[1] = fbxUv.mData[1];
					break;
				}
			}
			break;
		}
		case FbxLayerElementUV::eByPolygonVertex:
		{
			// �����￡ �ϳ� ������ ���̷�Ʈ�� �����͵� �ȴ�.
			switch (_uv->GetReferenceMode())
			{
				case FbxLayerElementUV::eDirect:
				//{
				//	FbxVector2 fbxUv = _uv->GetDirectArray().GetAt(_uvIdx);
				//	_dst.mData[0] = fbxUv.mData[0];
				//	_dst.mData[1] = fbxUv.mData[1];
				//	break;
				//}
				case FbxLayerElementUV::eIndexToDirect:
				{
					//int id = _uv->GetIndexArray().GetAt(_uvIdx);
					//FbxVector2 fbxUv = _uv->GetDirectArray().GetAt(id);
					//_dst.mData[0] = fbxUv.mData[0];
					//_dst.mData[1] = fbxUv.mData[1];

					FbxVector2 fbxUv = _uv->GetDirectArray().GetAt(_uvIdx); // ���̷�Ʈ�� �������� ��.
					_dst.mData[0] = fbxUv.mData[0];
					_dst.mData[1] = fbxUv.mData[1];
					break;
				}
			}
			break;
		}
		
	}

	return true;
}

bool FBXLoader::ReadColorCoord(FbxLayerElementVertexColor* _color, int _vertexIdx, int _colorIdx, FbxColor& _dst)
{
	if (_color == nullptr)
	{
		return false;
	}

	// �ؽ�ó ���� ����� �������� ����.
	// EMappingMode
	// eNone: ������ �������� �ʾҴ�.
	// eByControlPoint: ���������� 1���� ������ �Ǿ� �ִ�. (�� ������ UV��ǥ�� ��� ����.)
	// eByPolygonVertex: �� ������ ���� �����￡ ���ο� ��ǥ�� �ִ�. (�����￡�� Ž�� �ؾ���)
	// eByPolygon: ��ü �����￡ ���� ��ǥ�� �ִ�. 
	// eByEdge: ������ 1���� ���� ��ǥ�� �ִ�.
	// eAllSame: ��ü �����￡ 1���� ���� ��ǥ�� �ִ�.
	// ���� ��� -> ���� ��� Ȯ�� �ʿ�. == Reference Mode
	// eDirect: ����Ʈ�� ����Ǿ� ����. N��° ���� ������ DirectArray�� N��° ��ġ�� �ִ�.
	// eIndex: FBX 5.0 ���� �������� ���Ǿ���. ������ ������� ����. �� �̻��� ���������� eIndexToDirect�� ��ü��.
	// eIndexToDirect: �ε����� ����Ǿ� ����. 
	switch (_color->GetMappingMode())
	{
	case FbxLayerElementUV::eByControlPoint:
	{
		// ���� ���� UV�� 1���� ������ �ش� Vertex���� ������ ������.
		switch (_color->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			_dst = _color->GetDirectArray().GetAt(_vertexIdx);
			break;
		}
		case FbxLayerElementUV::eIndexToDirect:
		{
			int id = _color->GetIndexArray().GetAt(_vertexIdx);
			_dst = _color->GetDirectArray().GetAt(id);
			break;
		}
		}
		break;
	}
	case FbxLayerElementUV::eByPolygonVertex:
	{
		// �����￡ �ϳ� ������ ���̷�Ʈ�� �����͵� �ȴ�.
		switch (_color->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
			//{
			//	FbxVector2 fbxUv = _uv->GetDirectArray().GetAt(_uvIdx);
			//	_dst.mData[0] = fbxUv.mData[0];
			//	_dst.mData[1] = fbxUv.mData[1];
			//	break;
			//}
		{
			_dst = _color->GetDirectArray().GetAt(_colorIdx); // ���̷�Ʈ�� �������� ��.
			break;
		}
		case FbxLayerElementUV::eIndexToDirect:
		{
			//int id = _uv->GetIndexArray().GetAt(_uvIdx);
			//FbxVector2 fbxUv = _uv->GetDirectArray().GetAt(id);
			//_dst.mData[0] = fbxUv.mData[0];
			//_dst.mData[1] = fbxUv.mData[1];

			//_dst = _color->GetDirectArray().GetAt(_colorIdx); // ���̷�Ʈ�� �������� ��.
			int id = _color->GetIndexArray().GetAt(_colorIdx);
			_dst = _color->GetDirectArray().GetAt(id);
			break;
		}
		}
		break;
	}

	}

	return true;
}

bool FBXLoader::ReadNormal(FbxLayerElementNormal* _normal, int _vertexIdx, int _normalIdx, FbxVector4& _dst)
{
	if (_normal == nullptr)
	{
		return false;
	}

	// �ؽ�ó ���� ����� �������� ����.
	// EMappingMode
	// eNone: ������ �������� �ʾҴ�.
	// eByControlPoint: ���������� 1���� ������ �Ǿ� �ִ�. (�� ������ UV��ǥ�� ��� ����.)
	// eByPolygonVertex: �� ������ ���� �����￡ ���ο� ��ǥ�� �ִ�. (�����￡�� Ž�� �ؾ���)
	// eByPolygon: ��ü �����￡ ���� ��ǥ�� �ִ�. 
	// eByEdge: ������ 1���� ���� ��ǥ�� �ִ�.
	// eAllSame: ��ü �����￡ 1���� ���� ��ǥ�� �ִ�.
	// ���� ��� -> ���� ��� Ȯ�� �ʿ�. == Reference Mode
	// eDirect: ����Ʈ�� ����Ǿ� ����. N��° ���� ������ DirectArray�� N��° ��ġ�� �ִ�.
	// eIndex: FBX 5.0 ���� �������� ���Ǿ���. ������ ������� ����. �� �̻��� ���������� eIndexToDirect�� ��ü��.
	// eIndexToDirect: �ε����� ����Ǿ� ����. 
	switch (_normal->GetMappingMode())
	{
	case FbxLayerElementUV::eByControlPoint:
	{
		// ���� ���� UV�� 1���� ������ �ش� Vertex���� ������ ������.
		switch (_normal->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			_dst = _normal->GetDirectArray().GetAt(_vertexIdx);
			break;
		}
		case FbxLayerElementUV::eIndexToDirect:
		{
			int id = _normal->GetIndexArray().GetAt(_vertexIdx);
			_dst = _normal->GetDirectArray().GetAt(id);
			break;
		}
		}
		break;
	}
	case FbxLayerElementUV::eByPolygonVertex:
	{
		// �����￡ �ϳ� ������ ���̷�Ʈ�� �����͵� �ȴ�.
		switch (_normal->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
			//{
			//	FbxVector2 fbxUv = _uv->GetDirectArray().GetAt(_uvIdx);
			//	_dst.mData[0] = fbxUv.mData[0];
			//	_dst.mData[1] = fbxUv.mData[1];
			//	break;
			//}
		{
			_dst = _normal->GetDirectArray().GetAt(_normalIdx); // ���̷�Ʈ�� �������� ��.
			break;
		}
		case FbxLayerElementUV::eIndexToDirect:
		{
			//int id = _uv->GetIndexArray().GetAt(_uvIdx);
			//FbxVector2 fbxUv = _uv->GetDirectArray().GetAt(id);
			//_dst.mData[0] = fbxUv.mData[0];
			//_dst.mData[1] = fbxUv.mData[1];

			//_dst = _color->GetDirectArray().GetAt(_colorIdx); // ���̷�Ʈ�� �������� ��.
			int id = _normal->GetIndexArray().GetAt(_normalIdx);
			_dst = _normal->GetDirectArray().GetAt(id);
			break;
		}
		}
		break;
	}

	}

	return true;
}

int FBXLoader::getSubMaterialIndex(FbxLayerElementMaterial* _material, int _polyIdx)
{
	// ���ι��
	//eNone,
	//eByControlPoint,  // ������
	//eByPolygonVertex, //  
	//eByPolygon, // �����︶�� �ٸ��� �ִ�.
	//eAllSame - ��üǥ�鿡 1���� ������ǥ�� �ִ�.
	int iSubMtrl = 0;
	if (_material != nullptr)
	{
		switch (_material->GetMappingMode())
		{
		case FbxLayerElement::eByPolygon:
		{
			// ���� ������ �迭�� ����Ǵ� ���
			switch (_material->GetReferenceMode())
			{
			case FbxLayerElement::eIndex:
			{
				iSubMtrl = _polyIdx;
			}break;
			case FbxLayerElement::eIndexToDirect:
			{
				iSubMtrl = _material->GetIndexArray().GetAt(_polyIdx);
			}break;
			}
		}
		default:
		{
			break;
		}
		}
	}
	return iSubMtrl;
}

DXTexture* FBXLoader::FindTexture(FbxSurfaceMaterial* _surface, const char* _name, std::wstring* _rst)
{
	if (_surface == nullptr)
	{
		return nullptr;
	}

	//static const char* sShadingModel;
	//static const char* sMultiLayer;
	//
	//static const char* sEmissive;
	//static const char* sEmissiveFactor;
	//
	//static const char* sAmbient;
	//static const char* sAmbientFactor;
	//
	//static const char* sDiffuse; // ������ ���� ����ϴ� �ؽ��� ���. ���� Diffuse�� ������ ����. �⺻ ���
	//static const char* sDiffuseFactor;
	//
	//static const char* sSpecular;
	//static const char* sSpecularFactor;
	//static const char* sShininess;
	//
	//static const char* sBump;
	//static const char* sNormalMap;
	//static const char* sBumpFactor;
	//
	//static const char* sTransparentColor;
	//static const char* sTransparencyFactor;
	//
	//static const char* sReflection;
	//static const char* sReflectionFactor;
	//
	//static const char* sDisplacementColor;
	//static const char* sDisplacementFactor;
	//
	//static const char* sVectorDisplacementColor;
	//static const char* sVectorDisplacementFactor;

	std::string textureName;
	auto prop = _surface->FindProperty(_name); 
	if (prop.IsValid())
	{
		const FbxFileTexture* fbxFile = prop.GetSrcObject<FbxFileTexture>();
		if (fbxFile != nullptr)
		{
			textureName = fbxFile->GetFileName();
			if (!textureName.empty())
			{
				std::filesystem::path path(textureName);
				std::wstring file = path.filename().c_str();
				std::wstring wstrPath = m_wstrResourceDir;
				wstrPath += file;
				if (_rst != nullptr)
				{
					_rst->assign(wstrPath.begin(), wstrPath.end());
				}

				if (DXTextureManager::getInstance()->Load(wstrPath))
				{
					DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(wstrPath);
					if (pTexture != nullptr)
					{
						return pTexture;
					}
					else
					{
						return nullptr;
					}
				}
			}
		}
	}
	
	return nullptr;
}

FbxAMatrix FBXLoader::getGeometryMatrix(FbxNode* _node)
{
	// ���� ���
	// Affine ����� ���� ��ȯ �� ��, �׳� ����� ��� ���� ���� �� �� ���
	FbxAMatrix geometryMatrix; // ���� ���. �ʱ� ���� ��ġ�� ��ȯ �� �� ���. ���� ���. �� ��Ʈ������ ������ �ٲ��� ������ ���� ��Ŀ��� ��ȯ. ���� ��ȯ.
	FbxVector4 translation = _node->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 rotation = _node->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 scale = _node->GetGeometricScaling(FbxNode::eSourcePivot);
	geometryMatrix.SetT(translation);
	geometryMatrix.SetR(rotation);
	geometryMatrix.SetS(scale);

	return geometryMatrix;
}

FbxAMatrix FBXLoader::getNormalMatrix(const FbxAMatrix& _src)
{
	// �븻 ������ ������� ��ġ ��ķ� ���� ��� ��.
	FbxAMatrix normalMatrix = _src;
	normalMatrix = normalMatrix.Inverse();
	normalMatrix = normalMatrix.Transpose();
	return normalMatrix;
}

FbxAMatrix FBXLoader::getWorldMatrix(FbxNode* _node)
{
	// ���� ���, �ִϸ��̼ǿ��� ��� �ϸ� �ȵ�. ������ �ۿ��� ����ؾ� �ϳ� �ӽ÷� ���
	FbxVector4 translation_World;
	if (_node->LclTranslation.IsValid())
	{
		translation_World = _node->LclTranslation;
	}

	FbxVector4 rotation_World;
	if (_node->LclRotation.IsValid())
	{
		rotation_World = _node->LclRotation;
	}

	FbxVector4 scale_World;
	if (_node->LclScaling.IsValid())
	{
		scale_World = _node->LclScaling;
	}

	FbxAMatrix worldMatrix;
	worldMatrix.SetT(translation_World);
	worldMatrix.SetR(rotation_World);
	worldMatrix.SetS(scale_World);

	return worldMatrix;
}

FBXObject* FBXLoader::getObject(std::wstring _key)
{
	auto it = m_ObjectMap.find(_key);
	if (it != m_ObjectMap.end())
	{
		return it->second.get();
	}

	return nullptr;
}

void FBXLoader::setResourceDirectory(std::wstring _dir)
{
	m_wstrResourceDir = _dir;
}
