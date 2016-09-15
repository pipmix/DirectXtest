#ifndef CAMERA_H
#define CAMERA_H

#include "Headers.h"
#include "DataTypes.h"


extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;


extern HWND hWnd;
extern HINSTANCE hInst;


extern ComPtr<ID3D11Buffer> constantBuffer_finalMatrix;



 class Camera {

	public:

		// Camera Functions
						Camera();
		void			Update();
		void			Draw();

		void			MoveTo(float posX, float posY, float posZ);
		void			MoveBy(float vecX, float vecY, float vecZ);

		void			SetTarget(float tx, float ty, float tz);
		void			MoveTowardsTarget();

		void			UpdateCameraMatrix();
		void			UpdateScreenMatrix();
		void			UpdateCameraScreenMatrix();
		void			UpdateAllMatrices();
		
		const XMMATRIX	GetCameraScreenMatrix();
		const XMMATRIX	GetCameraMatrix();
		const XMMATRIX	GetScreenMatrix();
		const XMMATRIX	GetUIScreenMatrix();
		const XMMATRIX	GetUICameraMatrix();

		XMFLOAT2		ConvertMouseCoord(XMFLOAT2 mc);

 private:
		// Camera Matrices
		XMFLOAT4X4		_CameraScreenMatrix;
		XMFLOAT4X4		_CameraMatrix;
		XMFLOAT4X4		_ScreenMatrix;

		XMFLOAT4X4		_UIScreenMatix;;
		XMFLOAT4X4		_UICameraMatrix;

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

		XMFLOAT3		_target;

		long m_screenX, m_screenY;


 };

#endif //CAMERA_H