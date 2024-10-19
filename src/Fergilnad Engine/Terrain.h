// Terrain

#ifndef _Terrain
#define _Terrain

#include "AzulCore.h"
#include "GpuVertTypes.h"
#include "TextureTGA.h"

class Collidable;

class Terrain
{
public:
	Terrain();
	Terrain(const Terrain& other) = delete;
	Terrain& operator=(const Terrain& other) = delete;
	~Terrain();

	Terrain(const char* heightmapFile, int sidelen, float maxheight = 1.0f, float zeroalt = 0.0f, std::string texkey = "blue", float urepeat = 1.0f, float vrepeat = 1.0f);

	struct AABBData
	{
		float minx;
		float maxx;
		float miny;
		float maxy;
		float minz;
		float maxz;
	};

	struct Cell
	{
		Cell() {};

		Cell(int _x, int _z)
		{
			x = _x;
			z = _z;
		}

		int x;
		int z;
	};

	/// <summary>
	/// Creates the vertices list for the terrain
	/// </summary>
	/// <param name="verts">Array for the vertices</param>
	/// <param name="imgData">Image to base terrain on</param>
	void CreateVertsList(VertexStride_VUN* verts, GLbyte* imgData);
	/// <summary>
	/// Creates the triangles for the terrain
	/// </summary>
	/// <param name="tris">Array for the triangles</param>
	/// <param name="verts">Array for the terrain's vertices</param>
	void CreateTrisList(TriangleIndex* tris, VertexStride_VUN* verts);

	/// <summary>
	/// Renders the terrain
	/// </summary>
	/// <param name="cam">The camera that the terrain will be rendered on</param>
	virtual void Render(Camera* cam);

	/// <summary>
	/// Based on the vertex's row and col position, gives the vertex's index in the vertex list
	/// </summary>
	/// <param name="i">Row number</param>
	/// <param name="j">Column number</param>
	/// <returns>Vertex index</returns>
	int VertexIndex(int i, int j);
	/// <summary>
	/// Based on the vertex position, gives the index of the triangle it belongs to
	/// </summary>
	/// <param name="i">Row number of vertex</param>
	/// <param name="j">Column number of vertex</param>
	/// <returns></returns>
	int TriIndex(int i, int j);

	/// <summary>
	/// Depending on the vertex's x position, gives the u(v) coordinate for that position
	/// </summary>
	/// <param name="x">X position</param>
	/// <returns></returns>
	float UCoord(float x);
	/// <summary>
	/// Gives the (u)v coordinate depending on the z position
	/// </summary>
	/// <param name="z">Z position for the coordinate</param>
	/// <returns></returns>
	float VCoord(float z);

	/// <summary>
	/// Sets the terrain cell min and max points depending on its vertices
	/// </summary>
	/// <param name="index">Index in the terrain cell array</param>
	/// <param name="v1">First vertex</param>
	/// <param name="v2">Second vertex</param>
	/// <param name="v3">Thrid vertex</param>
	/// <param name="v4">Fourth vertex</param>
	void SetCellMinMax(int index, VertexStride_VUN v1, VertexStride_VUN v2, VertexStride_VUN v3, VertexStride_VUN v4);
	/// <summary>
	/// Highlights a cell that the point is within
	/// </summary>
	/// <param name="pos"></param>
	void GetCellFromPos(Vect pos);

	/// <summary>
	/// Renders the given cell in a given color
	/// </summary>
	/// <param name="c">The cell to be rendered</param>
	/// <param name="col">Color to render the cell in</param>
	void ShowCell(Cell c, Vect col);
	/// <summary>
	/// Shows the cell normal based on a point
	/// </summary>
	/// <param name="c">Cell</param>
	/// <param name="pos">Position to determine where on the cell the normal is calculated</param>
	void ShowCellNormal(Cell c, Vect pos);

	/// <summary>
	/// Gives the cell index according to its row and column index
	/// </summary>
	/// <param name="x">Column number</param>
	/// <param name="z">Row number</param>
	/// <returns></returns>
	int GetCellIndex(int x, int z);

	/// <summary>
	/// Gives the cell's min point
	/// </summary>
	/// <param name="c">Cell</param>
	/// <returns>A vector for the cell's min point</returns>
	Vect GetCellMin(Cell c);
	/// <summary>
	/// Gives the cell's max point
	/// </summary>
	/// <param name="c">Cell</param>
	/// <returns>A vector for the cell's max point</returns>
	Vect GetCellMax(Cell c);

	/// <summary>
	/// Gives a cell that a point corresponds to 
	/// </summary>
	/// <param name="pos">Position to determine cell</param>
	/// <returns>Cell that a point is within</returns>
	Cell GetCell(Vect pos);

	/// <summary>
	/// Gives the terrain's world Matrix
	/// </summary>
	/// <returns></returns>
	Matrix GetWorld();

private:
	AABBData* CellData;
	GraphicsObject_WireframeConstantColor* pWireTerrain;
	GraphicsObject_TextureFlat* pTexTerrain;
	Model* pModel;
	//Vect* normallist;

	int NUM_VERTS;
	int NUM_TRIANGLES;
	int SIDE_LENGTH;
	int NUM_CELLS;

	float MAX_HEIGHT;
	float ZERO_ALT;
	float UREPEAT;
	float VREPEAT;
	float CELL_SIZE;
	float SCALEFACTOR;
	
};

#endif _Terrain