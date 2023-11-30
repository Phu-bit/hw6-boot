# Example 13
EXE=final

# Main target
all: $(EXE)

#  Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32 -lm
CLEAN=rm -f *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
RES=$(shell uname -r|sed -E 's/(.).*/\1/'|tr 12 21)
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=$(RES)
CXXFLG=$(CFLG) -std=c++14
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Dependencies
final.o: final.cpp CSCIx229.h imgui.h Globals.h
fatal.o: fatal.c CSCIx229.h
errcheck.o: errcheck.c CSCIx229.h
print.o: print.c CSCIx229.h
loadtexbmp.o: loadtexbmp.c CSCIx229.h
loadobj.o: loadobj.c CSCIx229.h
projection.o: projection.c CSCIx229.h
axesHelper.o: axesHelper.c CSCIx229.h
cube.o: cube.c CSCIx229.h
icosahedron.o: icosahedron.c CSCIx229.h
ball.o: ball.c CSCIx229.h
light.o: light.c CSCIx229.h
cylinder.o: cylinder.c CSCIx229.h
truncatedPyramid.o: truncatedPyramid.c CSCIx229.h
colors.o: colors.c CSCIx229.h
calculateNormalVector.o: calculateNormalVector.c CSCIx229.h
toriGate.o: toriGate.c CSCIx229.h
shaderCompile.o: shaderCompile.c CSCIx229.h
tessellatedPlane.o: tessellatedPlane.c CSCIx229.h
init.o: init.c CSCIx229.h
Globals.o: Globals.cpp Globals.h
ImGuiHelper.o: ImGuiHelper.cpp ImGuiHelper.h imgui.h Globals.h
imgui.o: imgui.cpp imgui.h imgui_internal.h
imgui_demo.o: imgui_demo.cpp imgui.h 
imgui_draw.o: imgui_draw.cpp imgui.h imgui_internal.h imstb_rectpack.h imstb_textedit.h imstb_truetype.h
imgui_widgets.o: imgui_widgets.cpp imgui.h imgui_internal.h
imgui_tables.o: imgui_tables.cpp imgui.h imgui_internal.h
imgui_impl_glut.o: imgui_impl_glut.cpp imgui.h imgui_internal.h
imgui_impl_opengl2.o: imgui_impl_opengl2.cpp imgui.h imgui_internal.h imgui_impl_opengl2.h




#  Create archive
imgui.a: imgui.o imgui_demo.o imgui_draw.o imgui_widgets.o imgui_tables.o imgui_impl_glut.o imgui_impl_opengl2.o
	ar -rcs $@ $^


CSCIx229.a:fatal.o errcheck.o print.o loadtexbmp.o loadobj.o projection.o axesHelper.o cube.o icosahedron.o ball.o light.o cylinder.o truncatedPyramid.o colors.o calculateNormalVector.o toriGate.o shaderCompile.o tessellatedPlane.o init.o Globals.o ImGuiHelper.o
	ar -rcs $@ $^

# Compile rules
.c.o:
	gcc -c $(CFLG)  $<
	
.cpp.o:
	g++ -c $(CXXFLG) $<

#  Link
final:final.o Globals.o ImGuiHelper.o CSCIx229.a  imgui.a
	g++ $(CFLG) -o $@ $^ $(LIBS)

#  Clean
clean:
	$(CLEAN)

