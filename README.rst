=====
gloom
=====

A minimalistic boilerplate for OpenGL with C++ derived from `Glitter`_. Its intended use is to get smaller OpenGL projects quickly up and running for the graphics courses at `NTNU`_.

The following libraries are included with this project:

+---------+---------------------------------------+
| Library | Function                              |
+=========+=======================================+
| `glad`_ | OpenGL function loader                |
+---------+---------------------------------------+
| `glfw`_ | Window creation and input handler     |
+---------+---------------------------------------+
| `glm`_  | OpenGL mathematics                    |
+---------+---------------------------------------+
| `stb`_  | Various libraries, e.g. image loading |
+---------+---------------------------------------+

Additional functionality can be added by altering ``CMakeLists.txt``.


Dependencies
============

* `CMake`_ (v.3.*) is used to generate platform-specific makefiles and workspaces.

Please refer to the individual library repositories for more information about additional dependencies.


Getting started
===============

Download
--------

The project and all third-party libraries can be downloaded by cloning this repository with the ``--recursive`` flag.

.. code-block:: bash

  git clone --recursive git@github.com:senbon/gloom.git

If you have already cloned the repository and missed the ``--recursive`` flag, then the following grabs all dependencies.

.. code-block:: bash

  git submodule update --init


Compilation
-----------

Linux (command-line)
~~~~~~~~~~~~~~~~~~~~

With all dependencies installed, compiling the project is as easy as running CMake followed by the ``make`` command.

.. code-block:: bash

  # Change into the directory where you want your makefiles
  cd ./gloom/build

  # Generate UNIX Makefile (point CMake to CMakeLists.txt)
  cmake ..

  # Execute make command
  make

  # Run executable
  ./gloom/gloom

Specific generators can also be specified with CMake if you want to create workspaces for an IDE, for example:

.. code-block::

  cmake -G "CodeBlocks - Unix Makefiles"


Windows (cmake-gui)
~~~~~~~~~~~~~~~~~~~

1. Set the source code file to the root directory containing ``CMakeLists.txt``
2. Binaries can be built in the directory of your choice, e.g. ``gloom\build\``
3. Click the configure button and select which generator you would like to use
4. Click the generate button
5. If your generator is an IDE such as Visual Studio, then open up the newly created .sln file and build ``ALL_BUILD``. After this you might want to set ``gloom`` as you StartUp Project.


Examples
========

Shader class
------------

The class for loading shaders can be used as follows:

.. code-block:: cpp

  #include "shader.hpp"

  // ...

  Gloom::Shader shader;
  shader.attach("path_to_vertex_shader.vert");
  shader.attach("path_to_fragment_shader.frag");
  shader.link();

If all you are going to use are vertex and fragment shaders, then the piece of code above can be replaced by this:

.. code-block:: cpp

  Gloom::Shader shader;
  shader.makeBasicShader("path_to_vertex_shader.vert",
                         "path_to_fragment_shader.frag");

The shader program can be activated and deactivated as needed after you have linked the attached shaders. Below is an example from inside the rendering loop:

.. code-block:: cpp

  // Activate shader program
  shader.activate();

  // Perform draw calls using, for example, glDrawArrays

  // Deactivate shader program
  shader.deactivate();

Remember to delete the shader program when exiting, e.g. ``shader.destroy();``.


.. Links

.. _Glitter: https://github.com/Polytonic/Glitter
.. _NTNU: https://www.ntnu.edu/
.. _glad: https://github.com/Dav1dde/glad
.. _glfw: https://github.com/glfw/glfw
.. _glm: https://github.com/g-truc/glm
.. _stb: https://github.com/nothings/stb
.. _CMake: https://cmake.org/
