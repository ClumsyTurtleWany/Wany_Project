#include "FBXLoader.hpp"

bool FBXLoader::initialize()
{
	m_pManager = FbxManager::Create(); // static으로 리턴 됨.
	if (m_pManager != nullptr)
	{
		m_pImporter = FbxImporter::Create(m_pManager, ""); // 유니코드 사용 안함. static으로 리턴 됨.
		if (m_pImporter == nullptr)
		{
			OutputDebugString(L"WanyCore::FBXLoader::initialize::Failed Create Fbx Importer.\n");
			return false;
		}
		//m_pScene = FbxScene::Create(m_pManager, ""); // Scene은 파일 마다 로드 해야함.

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

	FbxScene* pScene = FbxScene::Create(m_pManager, ""); // Scene은 파일 마다 로드 해야함.
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
//	FbxScene* pScene = FbxScene::Create(m_pManager, ""); // Scene은 파일 마다 로드 해야함.
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
//		// Mesh: 랜더 가능한 데이터
//		// Scene graph 형식(트리에 모든 정보를 다 넣어서 저장 후 사용 및 랜더링하는 방식) 이라고 부름.
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
		// Mesh: 랜더 가능한 데이터
		// Scene graph 형식(트리에 모든 정보를 다 넣어서 저장 후 사용 및 랜더링하는 방식) 이라고 부름.
		ParseMesh(pMesh, _dst);
		//return false;
	}

	int childCount = _node->GetChildCount(); // Child 갯수가 0이면 정적 매쉬, 0이 아니면 동적 매쉬로 볼 수 있음.
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

	FbxNode* pNode = _mesh->GetNode(); // 원래는 Mesh가 아닌 Node로 돌리는게 맞다.  
	// 각 페이스 별로 다른 텍스쳐를 사용 할 수 있다. 이것을 서브 머테리얼 이라고 함. (1개의 오브젝트에 여러개의 텍스쳐 사용)
	// 서브 머테리얼을 렌더링 하기 위해선 같은 텍스쳐를 사용하는 페이스들을 묶어서 출력.
	int MaterialCnt = pNode->GetMaterialCount(); // 텍스쳐가 붙은 갯수.
	
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
		// 텍스처 정보를 가져오기 위한 것. 보통 1개의 Surface에 24개 이상의 텍스쳐가 붙어 있다.(24종 이상의 텍스쳐 방식이 존재한다.)
		// 텍스쳐 맵을 가지고 있다(ex. 마스크 텍스처처럼 알파를 가진 놈들 등 여러가지 종류가 있음.)
		FbxSurfaceMaterial* pSurface = pNode->GetMaterial(idx);
		if (pSurface != nullptr)
		{
			//auto prop = pSurface->FindProperty(FbxSurfaceMaterial::sDiffuse); // 기존에 많이 사용하던 텍스쳐 방식. 보통 Diffuse는 무조건 있음. 기본 방식
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

	// Layer 개념 필요. 여러번에 걸쳐 동일한 곳에 랜더링 하는것 == 멀티 패스 랜더링. 텍스쳐로 치환하면 멀티 텍스처 랜더링.
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
	// 3정점 = 1폴리곤(Triangle) 일 수도 있고
	// 4정점 = 1폴리곤(Quad) 일 수도 있다.
	// 폴리곤 -> 페이스 -> 정점
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

		FbxVector4* pVertexPosition = _mesh->GetControlPoints(); // 제어점(Control point == Vertices). 정점의 시작 위치
		for (int faceIdx = 0; faceIdx < faceCount; faceIdx++)
		{
			// FBX는 시계 반대 방향임. DirectX와 좌표계 방향이 다르다. 
			// Max 좌표는 Y축이 Z축, Z축이 Y축, (DX.x == Max.x, DX.y = Max.z, DX.z = Max.y)
			// DX 기저 		Max 기저
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
//	FbxNode* pNode = _mesh->GetNode(); // 원래는 Mesh가 아닌 Node로 돌리는게 맞다. 
//	int textureCount = pNode->GetMaterialCount(); // 텍스쳐가 붙은 갯수. 
//	// 각 페이스 별로 다른 텍스쳐를 사용 할 수 있다. 이것을 서브 머테리얼 이라고 함. (1개의 오브젝트에 여러개의 텍스쳐 사용)
//	// 서브 머테리얼을 렌더링 하기 위해선 같은 텍스쳐를 사용하는 페이스들을 묶어서 출력.
//	std::string textureName;
//	std::vector<std::vector<Vertex>> subMtrlVertexList;
//	int subMtrl = 0;
//	for (int i = 0; i < textureCount; i++)
//	{
//		// 텍스처 정보를 가져오기 위한 것. 보통 1개의 Surface에 24개 이상의 텍스쳐가 붙어 있다.(24종 이상의 텍스쳐 방식이 존재한다.)
//		// 텍스쳐 맵을 가지고 있다(ex. 마스크 텍스처처럼 알파를 가진 놈들 등 여러가지 종류가 있음.)
//		FbxSurfaceMaterial* pSurface = pNode->GetMaterial(i);
//		if (pSurface != nullptr)
//		{
//			auto prop = pSurface->FindProperty(FbxSurfaceMaterial::sDiffuse); // 기존에 많이 사용하던 텍스쳐 방식. 보통 Diffuse는 무조건 있음. 기본 방식
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
//	// Layer 개념 필요. 여러번에 걸쳐 동일한 곳에 랜더링 하는것 == 멀티 패스 랜더링. 텍스쳐로 치환하면 멀티 텍스처 랜더링.
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
//	// 3정점 = 1폴리곤(Triangle) 일 수도 있고
//	// 4정점 = 1폴리곤(Quad) 일 수도 있다.
//	// 폴리곤 -> 페이스 -> 정점
//	//int faceCount = 0;
//	int basePolyIdx = 0; // Color
//	for (int polyIdx = 0; polyIdx < polyCount; polyIdx++)
//	{
//		int polySize = _mesh->GetPolygonSize(polyIdx);
//		int faceCount = polySize - 2;
//
//		FbxVector4* pVertexPosition = _mesh->GetControlPoints(); // 제어점(Control point == Vertices). 정점의 시작 위치
//		for (int faceIdx = 0; faceIdx < faceCount; faceIdx++)
//		{
//			// FBX는 시계 반대 방향임. DirectX와 좌표계 방향이 다르다. 
//			// Max 좌표는 Y축이 Z축, Z축이 Y축, (DX.x == Max.x, DX.y = Max.z, DX.z = Max.y)
//			// DX 기저 		Max 기저
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

	// 텍스처 맵핑 방식은 여러가지 있음.
	// EMappingMode
	// eNone: 맵핑이 결정되지 않았다.
	// eByControlPoint: 제어점마다 1개의 맵핑이 되어 있다. (각 정점이 UV좌표를 들고 있음.)
	// eByPolygonVertex: 각 정점이 속한 폴리곤에 맵핑에 좌표가 있다. (폴리곤에서 탐색 해야함)
	// eByPolygon: 전체 폴리곤에 맵핑 좌표가 있다. 
	// eByEdge: 엣지에 1개의 맵핑 좌표가 있다.
	// eAllSame: 전체 폴리곤에 1개의 맵핑 좌표가 있다.
	// 맵핑 방식 -> 저장 방식 확인 필요. == Reference Mode
	// eDirect: 리스트에 저장되어 있음. N번째 맵핑 정보가 DirectArray의 N번째 위치에 있다.
	// eIndex: FBX 5.0 이하 버전에서 사용되었음. 지금은 사용하지 않음. 그 이상의 버전에서는 eIndexToDirect로 대체됨.
	// eIndexToDirect: 인덱스에 저장되어 있음. 
	switch (_uv->GetMappingMode())
	{
		case FbxLayerElementUV::eByControlPoint:
		{
			// 정점 마다 UV가 1개씩 있으니 해당 Vertex에서 정보를 가져옴.
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
			// 폴리곤에 하나 있으니 다이렉트로 가져와도 된다.
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

					FbxVector2 fbxUv = _uv->GetDirectArray().GetAt(_uvIdx); // 다이렉트로 가져오면 됨.
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

	// 텍스처 맵핑 방식은 여러가지 있음.
	// EMappingMode
	// eNone: 맵핑이 결정되지 않았다.
	// eByControlPoint: 제어점마다 1개의 맵핑이 되어 있다. (각 정점이 UV좌표를 들고 있음.)
	// eByPolygonVertex: 각 정점이 속한 폴리곤에 맵핑에 좌표가 있다. (폴리곤에서 탐색 해야함)
	// eByPolygon: 전체 폴리곤에 맵핑 좌표가 있다. 
	// eByEdge: 엣지에 1개의 맵핑 좌표가 있다.
	// eAllSame: 전체 폴리곤에 1개의 맵핑 좌표가 있다.
	// 맵핑 방식 -> 저장 방식 확인 필요. == Reference Mode
	// eDirect: 리스트에 저장되어 있음. N번째 맵핑 정보가 DirectArray의 N번째 위치에 있다.
	// eIndex: FBX 5.0 이하 버전에서 사용되었음. 지금은 사용하지 않음. 그 이상의 버전에서는 eIndexToDirect로 대체됨.
	// eIndexToDirect: 인덱스에 저장되어 있음. 
	switch (_color->GetMappingMode())
	{
	case FbxLayerElementUV::eByControlPoint:
	{
		// 정점 마다 UV가 1개씩 있으니 해당 Vertex에서 정보를 가져옴.
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
		// 폴리곤에 하나 있으니 다이렉트로 가져와도 된다.
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
			_dst = _color->GetDirectArray().GetAt(_colorIdx); // 다이렉트로 가져오면 됨.
			break;
		}
		case FbxLayerElementUV::eIndexToDirect:
		{
			//int id = _uv->GetIndexArray().GetAt(_uvIdx);
			//FbxVector2 fbxUv = _uv->GetDirectArray().GetAt(id);
			//_dst.mData[0] = fbxUv.mData[0];
			//_dst.mData[1] = fbxUv.mData[1];

			//_dst = _color->GetDirectArray().GetAt(_colorIdx); // 다이렉트로 가져오면 됨.
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
	// 매핑방식
	//eNone,
	//eByControlPoint,  // 제어점
	//eByPolygonVertex, //  
	//eByPolygon, // 폴리곤마다 다를수 있다.
	//eAllSame - 전체표면에 1개의 매핑좌표가 있다.
	int iSubMtrl = 0;
	if (_material != nullptr)
	{
		switch (_material->GetMappingMode())
		{
		case FbxLayerElement::eByPolygon:
		{
			// 매핑 정보가 배열에 저장되는 방식
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
	auto prop = _surface->FindProperty(_name); // 기존에 많이 사용하던 텍스쳐 방식. 보통 Diffuse는 무조건 있음. 기본 방식
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
