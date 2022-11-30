# First render

## Buffers

- Create and bind a VAO
- Create a VBO, which contains the metaballs IDs
- Create an SSBO, which contains the position of the center of metaballs
- Create an SSBO for LinkedList (later Binary tree)
- Create an SSBO for the screen pixels, which are going to store the first element sof the linked list (later the root of the binary tree)
- Link the VBO to the correct attribute

## Uniforms

- Modell matrix - Identity Matrix
- View and Project matrices comes from the camera
- RayDir won't be needed

## Draw

- Bind vao
- _Bind SSBO_ ?
- glDrawArray with the number of the metaballs
- Unbind the vao

## Program

- ABufferGenVS.glsl
- ABufferBillboardGS.glsl
- AbufferGenFs.glsl

# Second render

## Geometry

- FullScreenQuad

## Buffers

- The SSBOs are the same (Same BurfferID)
- They need to be binded again
- Vao and stuff for the full screen quad

## Uniforms

- RayDirMatrix

# Classes

- **MetaballGeometry**:
  - Create a vbo for metaball indices
  - Call Draw on empty array with the number of the metaballs
  - Has 1 SSBO;
    - MetaballPositionBuffer (For metaball centers)
- **MetaballMesh**:
  - Stores the number of the metaballs
  - Stores the positions of the metaballs
- **MetaballMaterial**:
  - Has 2 SSBOs:
    - ScreenBuffer
    - LinkedListBuffer
