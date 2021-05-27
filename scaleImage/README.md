TARGA image scaling program
==========================

Purpose
-------
Parse the TARGA image and save a scaled copy of the provided image.


Project & System Configuration
------------------------------
[Required] : CMake 3.0 or above
Use cmake to create a Visual Studio solution. CMakeLists.txt for the same.
	Create Solution :
		1. Extract zip and copy [scaleImage] folder to a location.
		2. In same directory where scaleImage is copied create a [build] folder.
		3. Move inside the build folder and run command provided below in CMD/Powershell.
		4. Command [cmake -G "Visual Studio 16" ..\scaleImage\]
		5. If step 4 is successful. build folder will contain a Visual Studio solution.


Description
-----------
	Read a targa file and save a scaled copy of the image at the same locaton with new name.
	By default image is scaled to 50 percent using the nearest neighbour algorithm.
	Excepted image extensions are tga, icb, vda and vst.

		file [required]
			[string] this should be full path with filename and extension.
			Example : D:\User\Files\image_name.tga

		percentage [optional]
			[integer] this is the percentage by which we need to scale.
			If none provided default 50 will be used.

		algorithm [optional]
			[integer] this is the option to specify which algorithm we want to be used.
			0 -> Nearest neighbour
			1 -> Bilinear interpolation
			3 -> Create two copy by using both algorithms


Usage
-----
	Use the provided scaleImage.exe inside x32 or x64 .
	exe file percentage algorithm

	Relevant field are explained above in the description tag.

Output
------
A scaled copy of the image will be created at the same location with new name.
For example:
	[Original image name] : image.tga
	Case 1.
		algo    = Nearest Neighbour
		percent = 50
		[Output image name]   : NN_50_image.tga
	
	Case 2.
		algo    = Bilinear
		percent = 200
		[Output image name]   : BL_200_image.tga


LIMITATION
----------
Tested only for the targa images created via GIMP application [very few targa image sampel images over internet].
GIMP provide the way to export any image as targa file but with/without RLE and origin as top/bottom left.
Bilinear will not work with image having/using colormap information.
