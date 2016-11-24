#include "ModelLoading.h"

//http://ogldev.atspace.co.uk/www/tutorial22/tutorial22.html
GameObject * loadModelFromFile(const string & filename)
{
	LOG(INFO,"Attempting to load model %s",filename.c_str());
	GameObject *gameObject = new GameObject();
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	const aiScene* scene = aiImportFile(filename.c_str(), aiProcess_JoinIdenticalVertices|aiProcess_Triangulate | aiProcess_FlipUVs| aiProcess_GenSmoothNormals| aiProcess_CalcTangentSpace);

	if (scene)
	{
		LOG(INFO,"Parsing Model %s",filename.c_str());
		const aiMesh * mesh=scene->mMeshes[0];

		vector<int> indices;
		vector<Vertex> verts;

		for (int f = 0; f < mesh->mNumFaces; f++)
		{
			const aiFace * face = &mesh->mFaces[f];
			for (int i = 0; i < face->mNumIndices; i++)
			{
				int index = face->mIndices[i];
				indices.push_back(index);
			}
		}

		for (int v = 0; v < mesh->mNumVertices; v++)
		{
			Vertex ourV;

			aiVector3D position = mesh->mVertices[v];
			aiVector3D normal = mesh->mNormals[v];

			if (mesh->HasTangentsAndBitangents())
			{
				aiVector3D tangent = mesh->mBitangents[v];
				aiVector3D binormal = mesh->mTangents[v];

				ourV.tangent.x = mesh->mTangents[v].x;
				ourV.tangent.y = mesh->mTangents[v].y;
				ourV.tangent.z = mesh->mTangents[v].z;

				ourV.binormal.x = mesh->mTangents[v].x;
				ourV.binormal.y = mesh->mTangents[v].y;
				ourV.binormal.z = mesh->mTangents[v].z;

			}

			ourV.position = vec3(position.x, position.y, position.z);
			ourV.normal = vec3(normal.x, normal.y, normal.z);

			for (int t = 0; t < mesh->GetNumUVChannels(); t++)
			{
				if (mesh->HasTextureCoords(t))
				{
					aiVector3D textCoord = mesh->mTextureCoords[t][v];
					ourV.texCoords0 = vec2(textCoord.x, textCoord.y);
				}
			}

			verts.push_back(ourV);
		}


		gameObject->copyVertexData(&verts[0], verts.size(), &indices[0], indices.size());
	}
	else
	{
		LOG(ERROR,"Error Parsing Model %s",aiGetErrorString());
	}

	aiReleaseImport(scene);


	return gameObject;

	//ourV.tangent = vec3(tangent.x, tangent.y, tangent.z);
	//ourV.binormal = vec3(binormal.x, binormal.y, binormal.z);
}
