#Tested with Blender Version 2.73 for Linux
#To be put into blender/*blender version*/scripts/startup/
#Notes:
#	- The output file is going to be the same as the script, unless a functionality to specifiy a directory is added.
#Ideas:
#   - Have the vertex/face count as a comment after each object.
#   - Have the total vertex/face count at the end of the file.
import bpy
from bpy_extras import mesh_utils
import os
#1. Get all of the level geometry data first.
#	a.Loop through the 'WorldGeo' group.
#	   On each loop
#		I.Get the vertecies and indicies of the object.
#		II.Afterwards get the location in World Space of the object.
#
# Stored in this format 
#
# '#' Can be ignored and used as comments
#
# wg -- This will begin the world geometry section.
# wgo name -- This will begin a world geometry object section.'name' is a string for the name of the object. 'name' stems from the "bpy.data.objects[#indexNumber].name".
# wpos x/y/z -- 'x','y', and 'z' are the coordinates of the object in World Space. 'wpos' stands for world position.
# rot rotationX/rotationY/rotationZ --'rotationX', 'rotationY' and 'rotationZ' is the rotation of the object in euler angles.
# ov id/x/y/z -- A vertex of the said object. 'id' is an int which gets incremented as a new vertex is added to the object. 'x' ,'y' and 'z' are floating point numbers representing each vertex's respective coordinates. 'ov' stands for object vertex
# of idofvertex1/idofvertex2/idofvertex3 -- The three vertecies that are used to construct the face.'idofvertex#' are ints that are used to refrence vertecies.'of' stands for object face.
# uv_map location -- The location of the texuture.'location' is the path to the texture
# closewgo -- This will close the world geometry object section.
# closewg -- This will close the world geometry section.


fileName = ''
defaultName = 'level'

def IsNameUsed(names, name):
    for string in names:
        if(string == name):
            return True
    return False      

def ExportToTPMap():
    for root,dirs,files in os.walk("."):
        i = -1
        notQuit = True
        global fileName
        while(notQuit):
            i = i + 1
            notQuit = IsNameUsed(files, defaultName + str(i))
            fileName = defaultName + (str(i).replace("'","")) + '.tpmap'
    
            ######## End of file validation code ##############
            ###################################################

    #Starting actual function
    file = open(fileName,'w')
    #Just writing some metadata.
    file.write('#.tpmap is a file format meant to be used with the TPEngine. The file format is the way that levels are designed in the TPEngine.\n')
    file.write('#File format written by Todor Penchev.\n')
    file.write('#Exported from Blender {} \n'.format(bpy.app.version_string))

    #Check if the world geometry group exists.
    try:
        geoGroup = bpy.data.groups['WorldGeo']  
    except KeyError:
        print("'WorldGeo' group was not defined.")
        return 1

    #Write the start of the world geometry section.
    file.write('\nwg\n')
    
    for objects in geoGroup.objects:
        #Denoting the start of the object's data.
        file.write('\nwgo   {}\n'.format(objects.name))
        file.write('wpos    {}/{}/{}\n'.format(str(objects.location.x),str(objects.location.y),str(objects.location.z)))
        file.write('rot     {}/{}/{}\n'.format(str(objects.rotation_euler.x),str(objects.rotation_euler.y),str(objects.rotation_euler.z)))
        i = 0
        for vertices in objects.data.vertices:
            #Looping through all of the vertices of the mesh.
            file.write('ov      {}/{}/{}/{}\n'.format(str(i),str(vertices.co.x),str(vertices.co.y),str(vertices.co.z)))
            i = i + 1
        for polygons in objects.data.polygons:
            #Looping through all of the faces of the mesh.
            file.write('of      {}/{}/{}\n'.format(str(polygons.vertices[0]),str(polygons.vertices[1]),str(polygons.vertices[2])))
        #File path for the texture that is going to be used.        
        try:
            file.write('uv_map  {}\n'.format(objects.active_material.active_texture.image.filepath))
        except:
            print("WARNING: {} does not contain a texture. Script will continue but might not function within TPEngine\n".format(objects.name))
            #As a side note, maybe it should write a default texture to here.            
            file.write('uv_map  NO_TEXTURE\n')
        #Closing statment for the object and its data.
        file.write('closewgo\n')

    #Closing statment for the world geometry section. 
    file.write('closewg\n')
    file.close()

#Operator Class
class TPMapExporter(bpy.types.Operator):

    bl_idname = "export.tpmap"
    bl_label = "Export to TPMap"

    #Check if the file exists, if it does, simply increment the name so we don't overwrite it.

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




