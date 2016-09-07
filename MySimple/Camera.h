#ifndef CAMERA_H
#define CAMERA_H

#include "Headers.h"
#include "DataTypes.h"

extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;


extern HWND hWnd;
extern HINSTANCE hInst;



extern ComPtr<ID3D11Buffer> constantBuffer_finalMatrix;
//extern XMMATRIX cameraMatrix;
//extern XMMATRIX screenMatrix;
//extern XMMATRIX cameraScreenMatrix;


 class Camera {

	public:

		// Camera Functions
						Camera();
		void			Update();
		void			Draw();

		void			UpdateCameraMatrix();
		void			UpdateScreenMatrix();
		void			UpdateCameraScreenMatrix();
		void			UpdateAllMatrices();
		
		const XMMATRIX	GetCameraScreenMatrix();
		const XMMATRIX	GetCameraMatrix();
		const XMMATRIX	GetScreenMatrix();

 private:
		// Camera Matrices
		XMFLOAT4X4		_CameraScreenMatrix;
		XMFLOAT4X4		_CameraMatrix;
		XMFLOAT4X4		_ScreenMatrix;

		// Camera Settings
		XMFLOAT3		_CamPosition;
		XMFLOAT3		_CamLookAt;
		XMFLOAT3		_CamUpVector;
		float			_CamFOVangle;
		float			_CamAspectRatio;
		float			_CamNearClip;
		float			_CamFarClip;
		bool			_IsCamPerspective;
		bool			_IsCamLookAt;

 };

#endif //CAMERA_H