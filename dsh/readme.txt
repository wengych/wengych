Dashboard Demo Application
--------------------------------------------------------------------------------
The dashboard is a demo application which displays data using a pod layout. Data can be displayed using charts,
forms, data grids and links. Layouts can be modified by dragging and dropping pods to a different location and
minimizing, maximizing and restoring pod windows. Layout changes are saved using a local SharedObject. Layout
data is loaded from /data/pods.xml with values in pod.xml indicating which data files to load for a particular
pod.

File and Folder Descriptions
--------------------------------------------------------------------------------
main.mxml - The main application file.
/assets - Contains assets which are embedded into the app.
/com - Contains ActionScript and MXML components.
/data - Contains the XML data file.
/qs - Contains ActionScript classes from www.quietlyscheming.com for chart effects.

Building the Application
--------------------------------------------------------------------------------
To build the project, create a project in Flex Builder using the included files and run "main.mxml".

Deploying the Application
--------------------------------------------------------------------------------
To deploy the project on a webserver, copy the auto-generated JS, HTML and SWF files from bin and the data folder
to your web server.