all: main

main: main.cpp ../shaders/shader.cpp ../shaders/shader.h ../imgui/imgui.cpp ../imgui/imgui_demo.cpp ../imgui/imgui_draw.cpp ../imgui/imgui_tables.cpp ../imgui/imgui_widgets.cpp ../imgui//imgui_impl_glfw.cpp ../imgui//imgui_impl_opengl3.cpp
	g++ main.cpp ../shaders/shader.cpp ../imgui/imgui.cpp ../imgui/imgui_demo.cpp ../imgui/imgui_draw.cpp ../imgui/imgui_tables.cpp ../imgui/imgui_widgets.cpp ../imgui//imgui_impl_glfw.cpp ../imgui//imgui_impl_opengl3.cpp -std=c++11 -o main -lglfw -lglew -framework OpenGL

