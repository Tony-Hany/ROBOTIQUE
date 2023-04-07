# Epuck2 Robot: Tape Follower
This project is designed to make the Epuck2 robot follow a specific color of tape on the ground in order to reach a specified location. The robot uses ChibiOS and multithreading to achieve this goal.

## Requirements
In order to run this project, you will need the following:
- An Epuck2 robot
- A computer with a USB port
- A ChibiOS development environment set up on your computer
- A tape with the desired color

## Setup
- Connect the Epuck2 robot to your computer via USB.
- Clone this repository to your computer.
- Build the project using ChibiOS.
- Upload the compiled code to the Epuck2 robot.
- Place the robot at the starting location, with the tape color selector set to the desired color.
- Set the destination location in the code.

## Usage
Once the robot is set up and the code is uploaded, it will automatically begin following the tape of the specified color. The robot uses multithreading to ensure that it can both follow the tape and avoid obstacles in its path.
If the robot encounters an obstacle, it will use its proximity sensors to determine the best path around it. Once it reaches the destination location, it will stop moving.

## Contributing
If you would like to contribute to this project, please follow these steps:
- Fork this repository.
- Create a new branch: git checkout -b my-new-feature
- Make changes to the codebase.
- Commit your changes: git commit -am 'Add some feature'
- Push the branch to the remote repository: git push origin my-new-feature
- Create a new pull request on GitHub.
  
# Help
## Makefile
### Project, sources and paths section:
This section of the makefile defines important variables such as:
- PROJECT: Stores the project name
- CSRC: Stores the .c source code file names
- ASMSRC: Stores the .s source code file names
- INCDIR: Stores the paths to the header files used in the project
- LIBS: Stores the names of the libraries used in the project.
- LIBDIR: Stores the paths to the directories where the libraries are located.
- LIB_OBJ: Stores the names of the library object files.
- LDSCRIPT: Stores the name of the linker script.
- DEFS: Stores the definitions that are passed to the compiler.
- OBJS: Stores the names of the object files that are generated during compilation
Note: $(CSRC:.c=.o) $(ASMSRC:.s=.o)	changes .c and .s with .o using => $(var:old=new)
- IINCDIR: adds the -I option to each path in INCDIR. This is used to tell the compiler where to look for header files using $(patsubst %,-I%,$(INCDIR))
- LLIBDIR: adds the -L option to each path in LIBDIR. This is used to tell the linker where to look for libraries using $(patsubst %,-L%,$(LIBDIR))

### Compiler options section:
#### Optimisation
There are some optimisation options that can be done by the compiler such as:
- -O0 = no optimisation can be set to -O1 -O2 or -O3
- -ggdb = generate debug information for gdb
- -fomit-frame-pointer = omit frame pointers (The frame pointer is a register that is typically 
used to point to the current function's stack frame. By using this option The compiler avoids generating code that saves and restores the frame pointer value for each function call.
the generated code uses fewer instructions and less stack space)
                        IF DIFFICULT DEBUGGING TRY REMOVING THIS OPTION
- -falign-functions=16 = align functions on a 16-byte boundary (the starting address of each function will be a multiple of 16. aims to improve performance by reducing cache misses when executing code. By aligning functions on a boundary, the cache can load more code in fewer accesses, potentially improving the speed of execution.)
                MAY INCREASE SIZE OF THE COMPILED CODE AND AFFECT PERFORMANCE 
- -ffunction-sections = place each function in its own section (each function will be put in it's own memory section by the compiler. It's normally used can be useful for optimizing memory usage or for placing critical functions in a specific location for faster access may alse make it easier to remove unused code during the linking phase of the build process, as the linker can simply remove entire sections that are not used rather than trying to remove individual functions)
- -fdata-sections = place each variable in its own section
- -fno-common = do not allow multiple definitions of global variables
There are also some optimisation options that are thumb specific which is simply a reduced instruction set used on some ARM processors. the recommended options are:
- -mthumb = generate code for the ARM Thumb instruction set, which is a compact 16-bit instruction set. Thumb code can be up to 65% smaller than equivalent ARM code
- -mno-thumb-interwork = generate code that does not support interworking between Thumb and ARM code. Interworking is the ability to switch between Thumb and ARM code, which requires some additional overhead in the generated code. By disabling interworking, the code can be smaller and simpler, but it also means that the code cannot call between ARM and Thumb functions.
                    REMOVE THIS OPTION IF YOU WANT TO CALL BETWEEN ARM AND THUMB
#### Warnings
We can also choose which warnings we want to be displayed during the compilation of the code. These options include:
- -Wall = all warnings (enables a set of commonly used warning options in GCC, but it does not enable all possible warnings)
- -Wextra = extra warnings (enables more warning messages than -Wall. It includes extra warnings about questionable coding practices that could lead to bugs or portability issues)
- -Wundef = undefined symbol warnings (generates a warning for any undefined preprocessor symbols encountered during compilation. This can be useful to detect potential errors in the use of preprocessor macros)
- -Wstrict-prototypes = function prototypes warnings (generates warnings for function declarations that do not include parameter types. This option is intended to catch potential issues where the actual arguments passed to a function do not match the expected type)

#### Flags
Finally, we can set the options using:
- CFLAGS: for the compiler
- ASFLAGS: for the assembler
- LDFLAGS: for the linker
Please note that some additional options have been added in this step such as:
- -MD -MP: specifies options for generating dependency files. These are files that track the dependencies between source files and headers.


