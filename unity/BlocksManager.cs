using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class BlocksManager : Singleton<BlocksManager> {
    /*
     * \brief Returns Block object reference corresponding to this instanceId
     * Returns null if not found
     */
    public Block getBlock(int instanceId){
        Block block = null;

        if (!this.blocks.TryGetValue (instanceId, out block)) {
            Debug.Assert (false, "Block not found with this instance id");
        }

        return block;
    }

    public Block buildLetter(Transform parent, char alphabet){
        Block block = this.getNextBlock (parent);

        // get letter from letter Mgr
        block.Letter = alphabet;

        // assign correctMesh
        block.Mesh = this.letterMeshes[Utility.LetterToInt(block.Letter)];

        return block;
    }

    /*
     * /brief BlockMgr always dispenses a block with getNextBlock()
     */
    protected Block getNextBlock(Transform parent){

        Block block = null;

        // return first not visible block
        foreach (Block blockVal in this.blocks.Values) {
            if (!blockVal.Active) {
                block = blockVal;
                break;
            }
        }

        Debug.Assert (block != null, "No visible=false blocks available to deQueue");

        // set block to be enabled
        block.Active = true;

        // set parent
//        block.Parent = parent;
		block.transform.SetParent(parent, false);

        // get letter from letter Mgr
        block.Letter = 'A';

        // assign correctMesh
        block.Mesh = this.letterMeshes[Utility.LetterToInt(block.Letter)];

        return block;
    }

    /*
     * This will recycle the given block 
     * and it will be available to be reused later on
     */
    public void recycle(Block block){
//		Debug.Log ("[BlocksManager]: Recycling block: " + block.Letter);

        block.Selected = false;

        block.Active = false;

        block.Parent = transform;
    }

	public void RecycleAllBlocks(){
		Debug.Log ("[BlocksManager]: Recycling all blocks");

		foreach (var block in this.blocks.Values) {
			this.recycle (block);
		}
	}

    private void insertBlock(Block block){
        Debug.Assert (block != null, "Null Block cannot be inserted");

        recycle (block);

//        Debug.Log ("Adding Block id: " + block.Id + " val: " + block.val);
        this.blocks.Add(block.Id, block);
    }

    private void createLetterMeshes(){
        this.letterMeshes = new Mesh[26]; // 26 alphabets
        this.selectedUVs = new Vector2[26][]; // 26 alternate UV verts for selected alphabets
		this.unSelectedUVs = new Vector2[26][]; // // 26 UV verts for unselected alphabets

        for (int letter = 0; letter< 26; ++letter) {
            int xSize = 1, ySize = 1; // grid of 1x1 aka quad

            Vector3[] vertices = new Vector3[(xSize+1) * (ySize+1)]; // 4 verts for a quad
            // generate vertices
            for (int i = 0, y = 0; y <= ySize; y++) {
                for (int x = 0; x <= xSize; x++, i++) {
                    vertices [i] = new Vector3 (x - 0.5f, y - 0.5f, 0f);
                }
            }

            int[] triangleIndices = new int[xSize * ySize * 6]; // 2 triangle => 6 indices
            triangleIndices[0] = 0;
            triangleIndices[1] = xSize + 1;
            triangleIndices[2] = 1;
            triangleIndices[3] = 1;
            triangleIndices[4] = xSize + 1;
            triangleIndices[5] = xSize + 2;

            int row = letter / 8;
            int col = letter % 8;

            // 2048 is total height
            // 256 is the width and height of a letter
            int numRows = 2048 / 256;

            // normalize width of letter between 0 and 1
            float size = 1.0f / numRows;

            Vector2[] UVs = new Vector2[]
            {
                new Vector2(size *  col,        1.0f - ((row+1) * size)),  // Bottom left
                new Vector2(size * (col+1),     1.0f - ((row+1) * size)),   // Bottom right
                new Vector2(size *  col,        1.0f - (row     * size)), // Top left
                new Vector2(size * (col+1),     1.0f - (row     * size)), // Top right
            };
			this.unSelectedUVs [letter] = UVs;

            Mesh mesh = new Mesh ();
            mesh.name = "Procedural Quad";
            mesh.vertices = vertices;
            mesh.triangles = triangleIndices;
            mesh.uv = UVs;

            this.letterMeshes [letter] = mesh;

            // populating selected uvs
            row += 4;
            Vector2[] selectUVs = new Vector2[]
            {
                new Vector2(size *  col,        1.0f - ((row+1) * size)),  // Bottom left
                new Vector2(size * (col+1),     1.0f - ((row+1) * size)),   // Bottom right
                new Vector2(size *  col,        1.0f - (row     * size)), // Top left
                new Vector2(size * (col+1),     1.0f - (row     * size)), // Top right
            };

            this.selectedUVs [letter] = selectUVs;
        }
    }

    public void setSelected(Block block, bool selected){
		if (selected) {
			block.Mesh.uv = this.selectedUVs [Utility.LetterToInt (block.Letter)];
		} else {
			block.Mesh.uv = this.unSelectedUVs [Utility.LetterToInt (block.Letter)];
		}

		block.Selected = selected;
    }

	#region Monobehavior methods

	protected override void Awake () {
		this.blocks = new Dictionary<int, Block> (Constants.NUM_ROWS * Constants.NUM_COLUMNS);

		for (int i = 0; i < (Constants.NUM_ROWS * Constants.NUM_COLUMNS); i++) {
			this.insertBlock(Instantiate<Block>(pfBlock));
		}

		createLetterMeshes ();

		pfBlock = null;

		base.Awake ();
	}

	protected new void OnDestroy(){
		Debug.Log ("[BlocksManager]: OnDestroy invoked");

		this.RecycleAllBlocks ();

		// releasing reference to the blocks
		this.blocks.Clear (); this.blocks = null;

		this.letterMeshes = null;

		for (int i = 0; i < 26; ++i) {
			this.selectedUVs [i] = null;
			this.unSelectedUVs [i] = null;
		}
		this.selectedUVs = null;
		this.unSelectedUVs = null;

		this.pfBlock = null;

		base.OnDestroy ();
	}

	#endregion

	#region Members
	public Block pfBlock; // prefab block
	private Mesh[] letterMeshes = null;
	private Vector2[][] selectedUVs = null;
	private Vector2[][] unSelectedUVs = null;

	private Dictionary<int, Block> blocks = null;
	#endregion
}
