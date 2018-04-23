#include "CGAL.h"
#include "CGALPrivatePCH.h"
#include "Core.h"
#include "ModuleManager.h"



#define LOCTEXT_NAMESPACE "FCGALModule"


#ifdef  TEST_CGAL_CODE //for testing if cgal's lib works fine

#include <CGAL/Simple_cartesian.h>
#include <CGAL/centroid.h>
#include <vector>
#include <iostream>
typedef double                      FT;
typedef CGAL::Simple_cartesian<FT>  K;
typedef K::Point_2                  Point_2;
typedef K::Point_3                  Point_3;
typedef K::Triangle_3               Triangle_3;
int TestFunc()
{
	// centroid of 2D points
	std::vector<Point_2> points_2;
	points_2.push_back(Point_2(1.0, 0.0));
	points_2.push_back(Point_2(2.0, 2.0));
	points_2.push_back(Point_2(3.0, 5.0));
	Point_2 c2 = CGAL::centroid(points_2.begin(), points_2.end(), CGAL::Dimension_tag<0>());
	std::cout << c2 << std::endl;
	// centroid of 3D points
	std::vector<Point_3> points_3;
	points_3.push_back(Point_3(1.0, 0.0, 0.5));
	points_3.push_back(Point_3(2.0, 2.0, 1.2));
	points_3.push_back(Point_3(3.0, 5.0, 4.5));
	Point_3 c3 = CGAL::centroid(points_3.begin(), points_3.end(), CGAL::Dimension_tag<0>());
	std::cout << c3 << std::endl;
	// centroid of 3D triangles
	std::list<Triangle_3> triangles_3;
	Point_3 p(1.0, 0.0, 0.0);
	Point_3 q(1.0, 2.0, 0.0);
	Point_3 r(0.0, 1.0, 3.0);
	Point_3 s(0.0, 2.0, 5.0);
	triangles_3.push_back(Triangle_3(p, q, r));
	triangles_3.push_back(Triangle_3(p, q, s));
	c3 = CGAL::centroid(triangles_3.begin(), triangles_3.end(), CGAL::Dimension_tag<2>());
	std::cout << c3 << std::endl;
	return 0;
}
#endif

void FCGALModule::StartupModule()
{
	
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FString BaseDir = /*"YOUR UE4 PROJECT PATH/Plugins/CGAL"*/FPaths::Combine(*FPaths::ProjectPluginsDir(),TEXT("CGAL")) ;

	// Add on the relative location of the third party dll and load it
	FString LIBGMP,LIBMPFR;
#if PLATFORM_WINDOWS
	LIBGMP = FPaths::Combine(*BaseDir, TEXT("ThirdParty/CGAL/libraries/Win64/libgmp-10.dll"));
	LIBMPFR = FPaths::Combine(*BaseDir, TEXT("ThirdParty/CGAL/libraries/Win64/libmpfr-4.dll"));
#endif // PLATFORM_WINDOWS

	LibraryHandle = !LIBGMP.IsEmpty() ? FPlatformProcess::GetDllHandle(*LIBGMP) : nullptr;
	LibraryHandle = !LIBMPFR.IsEmpty() ? FPlatformProcess::GetDllHandle(*LIBMPFR) : nullptr;
	//TestFunc();
#ifdef  TEST_CGAL_CODE
	TestFunc();
#endif
}

void FCGALModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	FPlatformProcess::FreeDllHandle(LibraryHandle);
	LibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCGALModule, CGAL)
