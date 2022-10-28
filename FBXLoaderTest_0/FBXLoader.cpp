#include "FBXLoader.hpp"

bool FBXLoader::initialize()
{
	m_pManager = FbxManager::Create();
	if (m_pManager != nullptr)
	{
		m_pImporter = FbxImporter::Create(m_pManager, ""); // �����ڵ� ��� ����.
		m_pScene = FbxScene::Create(m_pManager, "");

		return true;
	}
	else
	{
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
	if (m_pRoot != nullptr)
	{
		m_pRoot->Destroy();
		m_pRoot = nullptr;
	}	

	if (m_pScene != nullptr)
	{
		m_pScene->Destroy();
		m_pScene = nullptr;
	}

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

bool FBXLoader::Load(const char* _filename, std::vector<std::vector<Vertex>>& _dst)
{
	if (!m_pImporter->Initialize(_filename))
	{
		return false;
	}

	m_pImporter->Import(m_pScene);
	m_pRoot = m_pScene->GetRootNode();
	PreProcess(m_pRoot);

	for (auto it : m_MeshList)
	{
		std::vector<Vertex> vertexList;
		if (ParseMesh(it, vertexList))
		{
			_dst.push_back(vertexList);
		}
	}

	return true;
}

bool FBXLoader::PreProcess(FbxNode* _node)
{
	if (_node == nullptr)
	{
		return false;
	}

	FbxMesh* pMesh = _node->GetMesh();
	if (pMesh != nullptr)
	{
		// Mesh: ���� ������ ������
		// Scene graph ����(Ʈ���� ��� ������ �� �־ ���� �� ��� �� �������ϴ� ���) �̶�� �θ�.

		m_MeshList.push_back(pMesh);
	}

	int childCount = _node->GetChildCount();
	for (int idx = 0; idx < childCount; idx++)
	{
		FbxNode* pChild = _node->GetChild(idx);
		PreProcess(pChild);
	}
}

bool FBXLoader::ParseMesh(FbxMesh* _mesh, std::vector<Vertex>& _dst)
{
	if (_mesh == nullptr)
	{
		return false;
	}

	// Layer ���� �ʿ�. �������� ���� ������ ���� ������ �ϴ°� == ��Ƽ �н� ������. �ؽ��ķ� ġȯ�ϸ� ��Ƽ �ؽ�ó ������.
	std::vector<FbxLayerElementUV*> UVList;
	std::vector<FbxLayerElementVertexColor*> ColorList;
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
	}


	//std::vector<Vertex> vertexList;
	int polyCount = _mesh->GetPolygonCount();
	// 3���� = 1������(Triangle) �� ���� �ְ�
	// 4���� = 1������(Quad) �� ���� �ִ�.
	//int faceCount = 0;
	for (int polyIdx = 0; polyIdx < polyCount; polyIdx++)
	{
		int polySize = _mesh->GetPolygonSize(polyIdx);
		int faceCount = polySize - 2;

		FbxVector4* pVertexPosition = _mesh->GetControlPoints(); // ������(Control point == Vertices). ������ ���� ��ġ
		for (int faceIdx = 0; faceIdx < faceCount; faceIdx++)
		{
			int cornerIdx[3]; 
			// FBX�� �ð� �ݴ� ������. DirectX�� ��ǥ�� ������ �ٸ���. 
			// Max ��ǥ�� Y���� Z��, Z���� Y��, (DX.x == Max.x, DX.y = Max.z, DX.z = Max.y)
			// DX ���� 		Max ����
			// 1 0 0 0		1 0 0 0
			// 0 1 0 0		0 0 1 0
			// 0 0 1 0		0 1 0 0
			// 0 0 0 1		0 0 0 1
			
			// Texture
			// DX			Max
			// (0,0) (1,0)  (0,1) (1,1)
			// 
			// (0,1) (1,1)  (0,0) (1,0)
			//
			//

			cornerIdx[0] = _mesh->GetPolygonVertex(polyIdx, 0);
			cornerIdx[1] = _mesh->GetPolygonVertex(polyIdx, faceIdx + 2);
			cornerIdx[2] = _mesh->GetPolygonVertex(polyIdx, faceIdx + 1);
			for (int idx = 0; idx < 3; idx++)
			{
				int vertexIdx = cornerIdx[idx];
				FbxVector4 vertex = pVertexPosition[vertexIdx];
				Vector3f pos;
				pos.x = vertex.mData[0];
				pos.y = vertex.mData[2];
				pos.z = vertex.mData[1];
				
				Vector4f color = {1.0f, 1.0f, 1.0f, 1.0f};
				Vector2f texture;
				FbxVector2 tex; // = ;
				if (!UVList.empty())
				{
					if (ReadTextureCoord(UVList[0], vertexIdx, tex))
					{
						texture.x = tex.mData[0];
						texture.y = 1.0f - tex.mData[1];
					}
				}

				_dst.push_back(Vertex(pos, color, texture));
			}
		}
	}

	return true;
}

bool FBXLoader::ReadTextureCoord(FbxLayerElementUV* _uv, int _vertexIdx, FbxVector2& _dst)
{
	if (_uv == nullptr || _dst == nullptr)
	{
		return false;
	}

	//EMappingMode
	switch (_uv->GetMappingMode())
	{
		case FbxLayerElementUV::eByControlPoint:
		{
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
			switch (_uv->GetReferenceMode())
			{
				// Always enters this part for the example model
			case FbxLayerElementUV::eDirect: // fbx 5.0 ������ ��
			case FbxLayerElementUV::eIndexToDirect:
			{
				_dst.mData[0] = _uv->GetDirectArray().GetAt(0).mData[0];
				_dst.mData[1] = _uv->GetDirectArray().GetAt(0).mData[1];
				break;
			}
			}
			break;
		}
		
	}

	return true;
}