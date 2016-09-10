#include "Helpers.h"


void ReadDataFromFile(LPCWSTR filename, byte** data, UINT* size) {

	using namespace Microsoft::WRL;

	CREATEFILE2_EXTENDED_PARAMETERS extendedParams = {};
	extendedParams.dwSize = sizeof(CREATEFILE2_EXTENDED_PARAMETERS);
	extendedParams.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
	extendedParams.dwFileFlags = FILE_FLAG_SEQUENTIAL_SCAN;
	extendedParams.dwSecurityQosFlags = SECURITY_ANONYMOUS;
	extendedParams.lpSecurityAttributes = nullptr;
	extendedParams.hTemplateFile = nullptr;

	Wrappers::FileHandle file(CreateFile2(filename, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, &extendedParams));
	if (file.Get() == INVALID_HANDLE_VALUE) Error(L"Shader Load Error", filename);

	FILE_STANDARD_INFO fileInfo = {};
	if (!GetFileInformationByHandleEx(file.Get(), FileStandardInfo, &fileInfo, sizeof(fileInfo))) Error(L"Shader Load Error", filename);

	if (fileInfo.EndOfFile.HighPart != 0) throw std::exception();
	*data = reinterpret_cast<byte*>(malloc(fileInfo.EndOfFile.LowPart));
	*size = fileInfo.EndOfFile.LowPart;
	if (!ReadFile(file.Get(), *data, fileInfo.EndOfFile.LowPart, nullptr, nullptr)) Error(L"Shader Load Error", filename);



}

void Error(LPCWSTR header, LPCWSTR info)
{

	MessageBox(NULL, info, header, NULL);
}

bool IntersectsFloat(XMFLOAT4 & rectA, XMFLOAT4 & rectB){

	return (rectA.z > rectB.x && rectA.x < rectB.z &&
		rectA.w > rectB.y && rectA.y < rectB.w);


}

bool AABBIntersect2D(XMFLOAT4& rectA, XMFLOAT3 & pos, XMFLOAT3 & vel, XMFLOAT4& rectB ){
	//Intersect(p->collision, p->velocity, p->position);






}



