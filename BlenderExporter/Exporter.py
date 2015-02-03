#Tested with Blender Version 2.73 for Linux
#Notes:
#	- The output file is going to be the same as the script, unless a functionality to specifiy a directory is added.
#Ideas:
#   - Have the vertex/face count as a comment after each object.
#   - Have the total vertex/face count at the end of the file.
import bpy
from bpy_extras import mesh_utils
import os
###############Format Outline######################
#-------------------------------------------------#
# '#' Can be ignored and used as comments within the file.
#
# openwg -- This will open the world geometry section.
# openwgo name -- This will open a world geometry object section.'name' is a string for the name of the object. 'name' stems from the "bpy.data.objects[#indexNumber].name".
# wpos x/y/z -- 'x','y', and 'z' are the coordinates of the object in World Space. 'wpos' stands for world position.
# rot rotationX/rotationY/rotationZ --'rotationX', 'rotationY' and 'rotationZ' is the rotation of the object in euler angles.
# scale scaleX/scaleY/scaleZ -- 'scaleX', 'scaleY' and 'scaleZ' is the scale of the object.
# openov -- This will open the object vertex section.
# ov id/x/y/z -- A vertex of the said object. 'id' is an int which gets incremented as a new vertex is added to the object. 'x' ,'y' and 'z' are floating point numbers representing each vertex's respective coordinates. 'ov' stands for object vertex.
# closeov -- This will close the object vertex section.
# openof -- This will open the object face section.
# of idofvertex1/idofvertex2/idofvertex3 -- The three vertecies that are used to construct the face.'idofvertex#' are ints that are used to refrence vertecies.'of' stands for object face.
# closeof -- This will close the object face section.
# opent -- This will open the object texel section.
# ot vertexNumber/texelX/texelY/ -- A texel of the said object. 'texelX' and 'texelY' are the x and y texel coordinates.'vertexNumber' is the id of the vertex that is mapped to that UV coordinate.
# closet -- This will close the object texel section.
# uv_map name -- The location of the texuture.'location' is the path to the texture
# closewgo -- This will close the world geometry object section.
# closewg -- This will close the world geometry section.


fileName = ''
defaultName = 'level'
definedVertices = []
def isNameUsed(names, name):
    for string in names:
        if(string == name):
            return True            
    return False

def IsUVCoordForVertexDefined(vertex):
        if(len(definedVertices) == 0):
                definedVertices.append(vertex)
                return False
        for number in definedVertices:
             #   print(definedVertices)
                if vertex == number:
                        return True
                else:
                    #    print('Number:'.format(str(number)))
                        continue
        definedVertices.append(vertex)
        return False

def ExportToTPMap():
   
    #Check if the file exists, if it does, simply increment the name so we don't overwrite it.
    for root,dirs,files in os.walk("."):
        i = -1
        notQuit = True
        global fileName
        while(notQuit):
            i = i + 1
            notQuit = isNameUsed(files, defaultName + str(i) + '.tpmap')
        if(notQuit == False):
            fileName = defaultName + str(i) + '.tpmap'
            break  
    ######## End of file validation code ##############
    ###################################################

    #Check if the world geometry group exists.
    try:
        geoGroup = bpy.data.groups['WorldGeo'] 
    except KeyError:
        print("'WorldGeo' group was not defined.")
        return 1

    file = open('./' + fileName,'w')
    #Just writing some metadata.
    file.write('#.tpmap is a file format meant to be used with the TPEngine. The file format is the way that levels are designed in the TPEngine.\n')
    file.write('#File format written by Todor Penchev.\n')
    file.write('#Exported from Blender {} \n'.format(bpy.app.version_string))

    #Write the start of the world geometry section.
    file.write('\nopenwg\n')
    
    for objects in geoGroup.objects:
        #Denoting the start of the object's data.
        file.write('\nopenwgo {}\n'.format(objects.name))
        file.write('wpos /{}/{}/{}/\n'.format(str(objects.location.x),str(objects.location.y),str(objects.location.z)))
        file.write('rot /{}/{}/{}/\n'.format(str(objects.rotation_euler.x),str(objects.rotation_euler.y),str(objects.rotation_euler.z)))
        file.write('scale /{}/{}/{}/\n'.format(str(objects.scale.x),str(objects.scale.y),str(objects.scale.z)))
        file.write('openov\n')
        j = 0
        #Triangluate faces here. This might be removed if it ends up being obsolet.
        try:
                #Isnt working correctly.
                objects.select = True
                bpy.ops.object.mode_set(mode='EDIT')       
                bpy.ops.mesh.select_all(action='SELECT')
                bpy.ops.mesh.quads_convert_to_tris()
                bpy.ops.object.mode_set(mode='OBJECT')
                objects.select = False
        except:
                print("Did not triangluate correctly.")
                return 1
        for vertices in objects.data.vertices:
            #Looping through all of the vertices of the mesh.
            file.write('ov /{}/{}/{}/{}/\n'.format(str(j),str(vertices.co.x),str(vertices.co.y),str(vertices.co.z)))
            j = j + 1
        file.write('closeov\n')
        file.write('openof\n')
        for polygons in objects.data.polygons:
            #Looping through all of the faces of the mesh.
            file.write('of /{}/{}/{}/\n'.format(str(polygons.vertices[0]),str(polygons.vertices[1]),str(polygons.vertices[2])))
        file.write('closeof\n')
        file.write('opent\n')
        try:
                for polygons in objects.data.polygons:
                        vertexIndex = 0
                        for faces in polygons.loop_indices:
                                #Checking for redundant vertex cooridnate since faces can share UVs.
                                if IsUVCoordForVertexDefined(polygons.vertices[vertexIndex]):
                                        vertexIndex += 1
                                        continue
                                else:
                                        file.write('ot /{}/{}/{}/\n'.format(str(polygons.vertices[vertexIndex]),str(objects.data.uv_layers.active.data[faces].uv.x),str(objects.data.uv_layers.active.data[faces].uv.y)))
                                        vertexIndex += 1
        except:
                print("Not able to write UV coordinates. No UV mesh present, or some other error has occured.")
        file.write('closet\n')
	#File path for the texture that is going to be used.        
        try:
            file.write('uv_map {}\n'.format(objects.data.uv_textures.active.data[0].image.name))        
        except:
            print("WARNING: {} does not contain a texture. Script will continue but might not function correctly within the TPEngine.\n".format(objects.name))
            #As a side note, maybe it should write a default texture to here.            
            file.write('uv_map NO_TEXTURE\n')
        #Closing statment for the object and its data.
        file.write('closewgo\n')

    #Closing statment for the world geometry section. 
    file.write('closewg\n')
    file.close()
    #Reseting the list so we can export more than once in a session.
    del definedVertices[:]
    return 0

#Operator Class
class TPMapExporter(bpy.types.Operator):

    bl_idname = "export.tpmap"
    bl_label = "Export to TPMap"

    def execute(self, context):
        ExportToTPMap()
        return {'FINISHED'}

#Button Class
class ExportPanel(bpy.types.Panel):
    bl_label = "TPMap Exporter"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'TOOLS'
    
    def draw(self, context):
        layout = self.layout

        split = layout.split()
        col = split.column(align=True)
        col.operator("export.tpmap", text="Export To TPMap", icon='BLENDER')

def register():
    bpy.utils.register_class(TPMapExporter)
    bpy.utils.register_class(ExportPanel)

def unregister():
    bpy.utils.unregister_class(TPMapExporter)
    bpy.utils.unregister_class(ExportPanel)

if __name__ == "__main__":
    register()




