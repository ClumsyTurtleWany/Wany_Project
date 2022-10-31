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
		//m_pScene = FbxScene::Create(m_pManager, ""); // Scene�� ���� ���� �ε� �ؾ���.

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
	//if (m_pRoot != nullptr)
	//{
	//	m_pRoot->Destroy();
	//	m_pRoot = nullptr;
	//}	
	//
	//if (m_pScene != nullptr)
	//{
	//	m_pScene->Destroy();
	//	m_pScene = nullptr;
	//}
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
	/*std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filename = file.path().filename();
		std::wstring filepath = file.path();
		std::wstring extension = file.path().extension();

		if (extension == L"")
		{
			std::wstring dir = filepath + L"/";
			LoadDir(dir);
		}
		else
		{
			if (extension == L".FBX")
			{
				auto it = m_ObjectMap.find(_path);
				if (it != m_ObjectMap.end())
				{
					continue;
				}

				std::unique_ptr<FBXObject> Object = std::make_unique<FBXObject>();
				if (Load(path, Object.get()))
				{
					m_ObjectMap.insert(std::make_pair(_path, Object));
				}
			}
			else
			{
				continue;
			}
		}
	}*/

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

	FbxScene* pScene = FbxScene::Create(m_pManager, ""); // Scene�� ���� ���� �ε� �ؾ���.
	if (pScene == nullptr)
	{
		OutputDebugString(L"WanyCore::FBXLoader::Load::Failed Create Scene.\n");
		return false;
	}

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

//bool FBXLoader::Load(const char* _filename, std::vector<std::vector<Vertex>>& _dst)
//{
//	if (!m_pImporter->Initialize(_filename))
//	{
//		OutputDebugString(L"WanyCore::FBXLoader::Load::Failed Initialize Fbx Importer.\n");
//		return false;
//	}
//
//	FbxScene* pScene = FbxScene::Create(m_pManager, ""); // Scene�� ���� ���� �ε� �ؾ���.
//	if (pScene == nullptr)
//	{
//		return false;
//	}
//	m_pImporter->Import(pScene);
//
//	FbxNode* pRoot = pScene->GetRootNode();
//	if (pRoot == nullptr)
//	{
//		return false;
//	}
//	PreProcess(pRoot);
//
//	for (auto it : m_MeshList)
//	{
//		std::vector<Vertex> vertexList;
//		if (ParseMesh(it, vertexList))
//		{
//			_dst.push_back(vertexList);
//		}
//	}
//
//	pRoot->Destroy();
//	pScene->Destroy();
//
//	return true;
//}
//
//bool FBXLoader::PreProcess(FbxNode* _node, std::vector<FbxMesh*>& _meshList)
//{
//	if (_node == nullptr)
//	{
//		return false;
//	}
//
//	FbxMesh* pMesh = _node->GetMesh();
//	if (pMesh != nullptr)
//	{
//		// Mesh: ���� ������ ������
//		// Scene graph ����(Ʈ���� ��� ������ �� �־ ���� �� ��� �� �������ϴ� ���) �̶�� �θ�.
//
//		_meshList.push_back(pMesh);
//	}
//
//	int childCount = _node->GetChildCount();
//	for (int idx = 0; idx < childCount; idx++)
//	{
//		FbxNode* pChild = _node->GetChild(idx);
//		PreProcess(pChild, _meshList);
//	}
//
//	return true;
//}

bool FBXLoader::ParseNode(FbxNode* _node, FBXObject* _dst)
{
	if ((_node == nullptr) || (_dst == nullptr))
	{
		OutputDebugString(L"WanyCore::FBXLoader::ParseNode::Node or Dest is nullptr.\n");
		return false;
	}

	int totalGeometryObject = _node->GetDstObjectCount();
	FbxSkeleton* pSkeleton = _node->GetSkeleton();
	if (pSkeleton != nullptr)
	{
		int a = 0;
	}

	FbxObject* pObject = _node->GetDstObject();
	if(pObject != nullptr)
	{
		int a = 0;
		
	}

	FbxMesh* pMesh = _node->GetMesh();
	if (pMesh != nullptr)
	{
		// Mesh: ���� ������ ������
		// Scene graph ����(Ʈ���� ��� ������ �� �־ ���� �� ��� �� �������ϴ� ���) �̶�� �θ�.
		ParseMesh(pMesh, _dst);
		//return false;
	}

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

	return true;
}

bool FBXLoader::ParseMesh(FbxMesh* _mesh, FBXObject* _dst)
{
	if (_mesh == nullptr)
	{
		return false;
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
			//auto prop = pSurface->FindProperty(FbxSurfaceMaterial::sDiffuse); // ������ ���� ����ϴ� �ؽ��� ���. ���� Diffuse�� ������ ����. �⺻ ���
			//if (prop.IsValid())
			//{
			//	const FbxFileTexture* textureFile = prop.GetSrcObject<FbxFileTexture>();
			//	if (textureFile != nullptr)
			//	{
			//		textureName = textureFile->GetFileName();
			//		if (!textureName.empty())
			//		{
			//			std::filesystem::path path(textureName);
			//			std::wstring file = path.filename().c_str();
			//			std::wstring newPath = L"../resource/";
			//			newPath += file;
			//			if (DXTextureManager::getInstance()->Load(newPath))
			//			{
			//				DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(newPath);
			//				if (pTexture != nullptr)
			//				{
			//					_dst->Materials[idx]->setTexture(pTexture);
			//				}
			//			}
			//		}
			//	}
			//}
			DXTexture* pTexture = FindTexture(pSurface, FbxSurfaceMaterial::sDiffuse);
			if (pTexture != nullptr)
			{
				_dst->Materials[idx]->setTexture(pTexture);
			}
		}
	}

	// Layer ���� �ʿ�. �������� ���� ������ ���� ������ �ϴ°� == ��Ƽ �н� ������. �ؽ��ķ� ġȯ�ϸ� ��Ƽ �ؽ�ó ������.
	std::vector<FbxLayerElementUV*> UVList;
	std::vector<FbxLayerElementVertexColor*> ColorList;
	std::vector<FbxLayerElementMaterial*> MaterialList;
	
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
	}

	//std::vector<Vertex> vertexList;
	int polyCount = _mesh->GetPolygonCount();
	// 3���� = 1������(Triangle) �� ���� �ְ�
	// 4���� = 1������(Quad) �� ���� �ִ�.
	// ������ -> ���̽� -> ����
	//int faceCount = 0;
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

		FbxVector4* pVertexPosition = _mesh->GetControlPoints(); // ������(Control point == Vertices). ������ ���� ��ġ
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
				Vector3f pos;
				pos.x = vertex.mData[0];
				pos.y = vertex.mData[2];
				pos.z = vertex.mData[1];

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

				VertexList[MaterialIdx].push_back(Vertex(pos, color, texture));
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

//bool FBXLoader::ParseMesh(FbxMesh* _mesh, std::vector<Vertex>& _dst)
//{
//	if (_mesh == nullptr)
//	{
//		return false;
//	}
//
//	FbxNode* pNode = _mesh->GetNode(); // ������ Mesh�� �ƴ� Node�� �����°� �´�. 
//	int textureCount = pNode->GetMaterialCount(); // �ؽ��İ� ���� ����. 
//	// �� ���̽� ���� �ٸ� �ؽ��ĸ� ��� �� �� �ִ�. �̰��� ���� ���׸��� �̶�� ��. (1���� ������Ʈ�� �������� �ؽ��� ���)
//	// ���� ���׸����� ������ �ϱ� ���ؼ� ���� �ؽ��ĸ� ����ϴ� ���̽����� ��� ���.
//	std::string textureName;
//	std::vector<std::vector<Vertex>> subMtrlVertexList;
//	int subMtrl = 0;
//	for (int i = 0; i < textureCount; i++)
//	{
//		// �ؽ�ó ������ �������� ���� ��. ���� 1���� Surface�� 24�� �̻��� �ؽ��İ� �پ� �ִ�.(24�� �̻��� �ؽ��� ����� �����Ѵ�.)
//		// �ؽ��� ���� ������ �ִ�(ex. ����ũ �ؽ�óó�� ���ĸ� ���� ��� �� �������� ������ ����.)
//		FbxSurfaceMaterial* pSurface = pNode->GetMaterial(i);
//		if (pSurface != nullptr)
//		{
//			auto prop = pSurface->FindProperty(FbxSurfaceMaterial::sDiffuse); // ������ ���� ����ϴ� �ؽ��� ���. ���� Diffuse�� ������ ����. �⺻ ���
//			if (prop.IsValid())
//			{
//				const FbxFileTexture* textureFile = prop.GetSrcObject<FbxFileTexture>(0);
//				if (textureFile != nullptr)
//				{
//					textureName = textureFile->GetFileName();
//				}
//			}
//		}
//	}
//
//	if (!textureName.empty())
//	{
//		std::filesystem::path path(textureName);
//		std::wstring file = path.filename().c_str();
//	}
//
//	// Layer ���� �ʿ�. �������� ���� ������ ���� ������ �ϴ°� == ��Ƽ �н� ������. �ؽ��ķ� ġȯ�ϸ� ��Ƽ �ؽ�ó ������.
//	std::vector<FbxLayerElementUV*> UVList;
//	std::vector<FbxLayerElementVertexColor*> ColorList;
//	std::vector<FbxLayerElementMaterial*> MaterialList;
//	int layerCount = _mesh->GetLayerCount();
//	for (int layerIdx = 0; layerIdx < layerCount; layerIdx++)
//	{
//		FbxLayer* pLayer = _mesh->GetLayer(layerIdx);
//		FbxLayerElementUV* pUV = pLayer->GetUVs();
//		if (pUV != nullptr)
//		{
//			UVList.push_back(pUV);
//		}
//
//		FbxLayerElementVertexColor* pColor = pLayer->GetVertexColors();
//		if (pColor != nullptr)
//		{
//			ColorList.push_back(pColor);
//		}
//
//		FbxLayerElementMaterial* pMaterial = pLayer->GetMaterials();
//		if (pMaterial != nullptr)
//		{
//			MaterialList.push_back(pMaterial);
//		}
//	}
//
//
//	//std::vector<Vertex> vertexList;
//	int polyCount = _mesh->GetPolygonCount();
//	// 3���� = 1������(Triangle) �� ���� �ְ�
//	// 4���� = 1������(Quad) �� ���� �ִ�.
//	// ������ -> ���̽� -> ����
//	//int faceCount = 0;
//	int basePolyIdx = 0; // Color
//	for (int polyIdx = 0; polyIdx < polyCount; polyIdx++)
//	{
//		int polySize = _mesh->GetPolygonSize(polyIdx);
//		int faceCount = polySize - 2;
//
//		FbxVector4* pVertexPosition = _mesh->GetControlPoints(); // ������(Control point == Vertices). ������ ���� ��ġ
//		for (int faceIdx = 0; faceIdx < faceCount; faceIdx++)
//		{
//			// FBX�� �ð� �ݴ� ������. DirectX�� ��ǥ�� ������ �ٸ���. 
//			// Max ��ǥ�� Y���� Z��, Z���� Y��, (DX.x == Max.x, DX.y = Max.z, DX.z = Max.y)
//			// DX ���� 		Max ����
//			// 1 0 0 0		1 0 0 0
//			// 0 1 0 0		0 0 1 0
//			// 0 0 1 0		0 1 0 0
//			// 0 0 0 1		0 0 0 1
//			////////////////////////////
//			// Texture
//			// DX			Max
//			// (0,0) (1,0)  (0,1) (1,1)
//			// 
//			// (0,1) (1,1)  (0,0) (1,0)
//			/////////////////////////////
//			int cornerIdx[3]; 
//			cornerIdx[0] = _mesh->GetPolygonVertex(polyIdx, 0);
//			cornerIdx[1] = _mesh->GetPolygonVertex(polyIdx, faceIdx + 2);
//			cornerIdx[2] = _mesh->GetPolygonVertex(polyIdx, faceIdx + 1);
//
//			int UVidx[3] = { 0, };
//			UVidx[0] = _mesh->GetTextureUVIndex(polyIdx, 0);
//			UVidx[1] = _mesh->GetTextureUVIndex(polyIdx, faceIdx + 2);
//			UVidx[2] = _mesh->GetTextureUVIndex(polyIdx, faceIdx + 1);
//
//			int vertexColorIdx[3] = { 0, faceIdx + 2, faceIdx + 1 };
//			for (int idx = 0; idx < 3; idx++)
//			{
//				int vertexIdx = cornerIdx[idx];
//				FbxVector4 vertex = pVertexPosition[vertexIdx];
//				Vector3f pos;
//				pos.x = vertex.mData[0];
//				pos.y = vertex.mData[2];
//				pos.z = vertex.mData[1];
//				
//				Vector4f color = {1.0f, 1.0f, 1.0f, 1.0f};
//				Vector2f texture;
//				FbxVector2 tex; // = ;
//				int uvidx = UVidx[idx];
//				if (!UVList.empty())
//				{
//					if (ReadTextureCoord(UVList[0], vertexIdx, uvidx, tex))
//					{
//						texture.x = tex.mData[0];
//						texture.y = 1.0f - tex.mData[1];
//					}
//				}
//
//				if (!ColorList.empty())
//				{
//					int colorIdx = basePolyIdx + vertexColorIdx[idx];
//					FbxColor fbxColor;
//					if (ReadColorCoord(ColorList[0], vertexIdx, colorIdx, fbxColor))
//					{
//						color.x = fbxColor.mRed;
//						color.y = fbxColor.mGreen;
//						color.z = fbxColor.mBlue;
//						color.w = fbxColor.mAlpha;
//					}
//				}
//
//				_dst.push_back(Vertex(pos, color, texture));
//			}
//
//			
//		}
//
//		basePolyIdx += polyCount;
//	}
//
//	return true;
//}

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

DXTexture* FBXLoader::FindTexture(FbxSurfaceMaterial* _surface, const char* _name)
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
	//static const char* sDiffuse;
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
	auto prop = _surface->FindProperty(_name); // ������ ���� ����ϴ� �ؽ��� ���. ���� Diffuse�� ������ ����. �⺻ ���
	if (prop.IsValid())
	{
		const FbxFileTexture* textureFile = prop.GetSrcObject<FbxFileTexture>();
		if (textureFile != nullptr)
		{
			textureName = textureFile->GetFileName();
			if (!textureName.empty())
			{
				std::filesystem::path path(textureName);
				std::wstring file = path.filename().c_str();
				std::wstring newPath = L"../resource/";
				newPath += file;
				if (DXTextureManager::getInstance()->Load(newPath))
				{
					DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(newPath);
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

FBXObject* FBXLoader::getObject(std::wstring _key)
{
	auto it = m_ObjectMap.find(_key);
	if (it != m_ObjectMap.end())
	{
		return it->second.get();
	}

	return nullptr;
}
