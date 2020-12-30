// Terrain

#include "Terrain.h"
#include "FGNMathTools.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TextureManager.h"
#include "VisualizerAttorney.h"
#include "CollidableAttorney.h"
#include "Collidable.h"

Terrain::Terrain()
	:CellData(0), pWireTerrain(0), pTexTerrain(0), pModel(0)
{
}

Terrain::Terrain(const char* heightmapFile, int sidelen, float maxheight, float zeroalt, std::string texkey, float urepeat, float vrepeat)
	:SCALEFACTOR(5.0f)
{
	int imgWidth, imgHeight, icomp;
	unsigned int dtype;
	GLbyte* imgData = gltReadTGABits(heightmapFile, &imgWidth, &imgHeight, &icomp, &dtype);
	assert(imgWidth == imgHeight && imgWidth != 0);

	NUM_VERTS = FGNMathTools::NumVertsSquare(sidelen);
	NUM_TRIANGLES = FGNMathTools::NumTrisSquare(sidelen);
	SIDE_LENGTH = sidelen;
	MAX_HEIGHT = maxheight;
	ZERO_ALT = zeroalt;
	UREPEAT = urepeat;
	VREPEAT = vrepeat;
	NUM_CELLS = (SIDE_LENGTH - 1) * (SIDE_LENGTH - 1);
	CELL_SIZE = static_cast<float>(sidelen) / static_cast<float>(sidelen - 1) * SCALEFACTOR;

	CellData = new AABBData[NUM_CELLS];

	VertexStride_VUN* pVerts = new VertexStride_VUN[NUM_VERTS];
	CreateVertsList(pVerts, imgData);

	TriangleIndex* tlist = new TriangleIndex[NUM_TRIANGLES];
	CreateTrisList(tlist, pVerts);

	pModel = new Model(pVerts, NUM_VERTS, tlist, NUM_TRIANGLES);

	Vect v(0, 0, 255);
	pWireTerrain = new GraphicsObject_WireframeConstantColor(pModel, ShaderManager::Get("ColorConstant"), v);
	pTexTerrain = new GraphicsObject_TextureFlat(pModel, ShaderManager::Get("TextureFlat"), TextureManager::Get(texkey));

	delete[] pVerts;
	delete[] tlist;

	Matrix world = Matrix(SCALE, SCALEFACTOR, SCALEFACTOR, SCALEFACTOR);
	pWireTerrain->SetWorld(world);
	pTexTerrain->SetWorld(world);
}

Terrain::~Terrain()
{
	delete pModel;
	delete pWireTerrain;
	delete pTexTerrain;
	delete[] CellData;
}

void Terrain::CreateVertsList(VertexStride_VUN* verts, GLbyte* imgData)
{
	int index;
	int n = NUM_VERTS - 1;
	for (int i = 0; i < SIDE_LENGTH; i++)
	{
		for (int j = 0; j < SIDE_LENGTH; j++)
		{
			index = VertexIndex(i, j);
			float fl = static_cast<float>(SIDE_LENGTH);
			float fi = static_cast<float>(i);
			float fj = static_cast<float>(j);

			verts[index].x = (((fl / (fl - 1.0f)) * fj) - (fl / 2.0f));

			// if at max value
			if (static_cast<unsigned char>(imgData[n * 3]) == 255)
				verts[index].y = ZERO_ALT + (MAX_HEIGHT);
			// if the value is 0, the y value is the zero altitude
			else if (static_cast<unsigned char>(imgData[n * 3]) == 0)
				verts[index].y = ZERO_ALT;
			// ratio of the value:maxvalue, times the max height
			else
				verts[index].y = ZERO_ALT + ((static_cast<float>(static_cast<unsigned char>(imgData[n * 3])) / 255.0f) * MAX_HEIGHT);

			verts[index].z = ((fl / 2.0f) - ((fl / (fl - 1.0f)) * fi));
			verts[index].u = UCoord(fj);
			verts[index].v = VCoord(fi);
			verts[index].txt = 0;
			n--;
		}
	}
}

void Terrain::CreateTrisList(TriangleIndex* tris, VertexStride_VUN* verts)
{
	int n = 0;
	int index;

	for (int i = 0; i < SIDE_LENGTH - 1; i++)
	{
		for (int j = 0; j < SIDE_LENGTH - 1; j++)
		{
			index = TriIndex(i, j);

			tris[n].set(index, index + SIDE_LENGTH + 1, index + SIDE_LENGTH);
			tris[n + 1].set(index, index + 1, index + 1 + SIDE_LENGTH);

			SetCellMinMax(GetCellIndex(j, i), verts[index], verts[index + 1], verts[index + SIDE_LENGTH], verts[index + SIDE_LENGTH + 1]);

			n += 2;
		}
	}
}

void Terrain::Render(Camera* cam)
{
	//pWireTerrain->Render(cam);
	pTexTerrain->Render(cam);
}

void Terrain::ShowCell(Cell c, Vect col)
{
	int n = GetCellIndex(c.x, c.z);

	VisualizerAttorney::Show::AABB(Vect(CellData[n].minx, CellData[n].miny, CellData[n].minz), Vect(CellData[n].maxx, CellData[n].maxy, CellData[n].maxz), col);
}

void Terrain::ShowCellNormal(Cell c, Vect pos)
{
	Vect* vlist = pWireTerrain->getModel()->getVectList();
	TriangleIndex* tlist = pWireTerrain->getModel()->getTriangleList();

	int index = GetCellIndex(c.x, c.z);
	index *= 2;

	Vect v0, v1, v2, hit, normal, normal2;
	// Point is in the top triangle
	if (-(pos - (vlist[tlist[index].v1] * SCALEFACTOR)).X() > (pos - (vlist[tlist[index].v1] * SCALEFACTOR)).Z())
	{
		v0 = vlist[tlist[index].v0] * SCALEFACTOR;
		v1 = vlist[tlist[index].v1] * SCALEFACTOR;
		v2 = vlist[tlist[index].v2] * SCALEFACTOR;

		float b = -(pos - v1).X() / CELL_SIZE;
		float y = (pos - v1).Z() / CELL_SIZE;

		hit = v1 + (b * (v2 - v1)) + (y * (v0 - v2));

		normal = hit.cross(v1);
		normal.norm();
	}
	// Point is in the bottom triangle
	else
	{
		v0 = vlist[tlist[index + 1].v0] * SCALEFACTOR;
		v1 = vlist[tlist[index + 1].v1] * SCALEFACTOR;
		v2 = vlist[tlist[index + 1].v2] * SCALEFACTOR;

		float b = -(pos - v2).X() / CELL_SIZE;
		float y = (pos - v2).Z() / CELL_SIZE;

		hit = v2 + (y * (v1 - v2)) + (b * (v0 - v1));

		normal = hit.cross(v2);
		normal.norm();
	}

	//VisualizerAttorney::Show::Point(hit, Color::Yellow);
	VisualizerAttorney::Show::Point(hit + normal, Color::Green);
	VisualizerAttorney::Show::Line(hit, hit + normal, Color::Green);
}

Vect Terrain::GetCellMin(Cell c)
{
	int n = GetCellIndex(c.x, c.z);

	return Vect(CellData[n].minx, CellData[n].miny, CellData[n].minz);
}

Vect Terrain::GetCellMax(Cell c)
{
	int n = GetCellIndex(c.x, c.z);

	return Vect(CellData[n].maxx, CellData[n].maxy, CellData[n].maxz);
}

int Terrain::VertexIndex(int i, int j)
{
	return (SIDE_LENGTH * i) + j;
}

int Terrain::TriIndex(int i, int j)
{
	return j + (i * SIDE_LENGTH);
}

float Terrain::UCoord(float x)
{
	return x * UREPEAT / (SIDE_LENGTH - 1);
}

float Terrain::VCoord(float z)
{
	return VREPEAT - (VREPEAT * z / (SIDE_LENGTH - 1));
}

void Terrain::SetCellMinMax(int index, VertexStride_VUN v1, VertexStride_VUN v2, VertexStride_VUN v3, VertexStride_VUN v4)
{
	float max = v1.y;
	float min = v1.y;

	if (max < v2.y)
		max = v2.y;
	else if (min > v2.y)
		min = v2.y;
	if (max < v3.y)
		max = v3.y;
	else if (min > v3.y)
		min = v3.y;
	if (max < v4.y)
		max = v4.y;
	else if (min > v4.y)
		min = v4.y;

	CellData[index].miny = min * SCALEFACTOR;
	CellData[index].maxy = max * SCALEFACTOR;

	CellData[index].minx = v1.x * SCALEFACTOR;
	CellData[index].maxx = v2.x * SCALEFACTOR;
	CellData[index].minz = v3.z * SCALEFACTOR;
	CellData[index].maxz = v1.z * SCALEFACTOR;
}

void Terrain::GetCellFromPos(Vect pos)
{
	Cell c = GetCell(pos);

	int n = GetCellIndex(c.x, c.z);

	// Shows the normal of the face that the point is above
	ShowCellNormal(GetCell(pos), pos);

	// Highlight the cell directly below the point
	VisualizerAttorney::Show::AABB(Vect(CellData[n].minx, CellData[n].miny, CellData[n].minz), Vect(CellData[n].maxx, CellData[n].maxy, CellData[n].maxz), Color::Red);

	// Line connecting the cell to the point
	VisualizerAttorney::Show::AABB(Vect(pos.X(), CellData[n].maxy, pos.Z()), pos, Color::White);
}

int Terrain::GetCellIndex(int x, int z)
{
	return (z * (SIDE_LENGTH - 1)) + x;
}

Terrain::Cell Terrain::GetCell(Vect pos)
{
	int x = 0, z = 0;
	for (int i = SIDE_LENGTH - 1; i >= 0; i--)
	{
		if (pos.X() <= CellData[i].maxx)
			x = i;
	}

	for (int i = 0; i < SIDE_LENGTH - 1; i++)
	{
		if (pos.Z() <= CellData[i * (SIDE_LENGTH - 1)].maxz)
			z = i;
	}

	return Cell(x, z);
}

Matrix Terrain::GetWorld()
{
	return pWireTerrain->getWorld();
}