//////#include "Application.h"
////#include "DrawTriangle.h"
////
////int main() {
////	return DrawTriangle::GetSingleton().Run();
////}
//
//#include "BindableTesting.h"
//
//int main() {
//	BindableTesting demo;
//	demo.Run();
//}

#include "Application.h"

int main() {
	Application app("Hardware Accelarated 3D Renderer", 800, 600);
	app.Run();
	return 0;
}