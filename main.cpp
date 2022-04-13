#include <Windows.h>

//�E�B���h�E�v���V�[�W��
LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
	
	//���b�Z�[�W�ɉ����ăQ�[���ŗL�̏������s��
	switch (msg) {

	//�E�B���h�E���j�����ꂽ
	case WM_DESTROY:
		//OS�ɑ΂��ăA�v���̏I����`����(delete�݂����ȁA����������̖���)
		PostQuitMessage(0);
		return 0;
	}

	//�W���̃��b�Z�[�W�������s��
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

//windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//�E�B���h�E�T�C�Y
	const int window_width = 1200;
	const int window_height = 720;

	//�E�B���h�E�N���X�̐ݒ�
	WNDCLASSEX w{};
	w.cbSize = sizeof(WNDCLASSEX);			//�E�B���h�E�v���V�[�W����ݒ�
	w.lpfnWndProc = (WNDPROC)WindowProc;	//�E�B���h�E�N���X��
	w.lpszClassName = L"DirectXGame";		//�E�B���h�E�n���h��
	w.hCursor = LoadCursor(NULL, IDC_ARROW);//�J�[�\���w��

	//�E�B���h�E�N���X��OS�ɓo�^����
	RegisterClassEx(&w);

	//�E�B���h�E�T�C�Y { X���W Y���W ���� �c�� }
	RECT wrc = { 0,0,window_width,window_height };

	//�����ŃT�C�Y��␳����
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//�E�B���h�E�I�u�W�F�N�g�̐���

	//�R���\�[���ւ̕����o��
	OutputDebugStringA("Hello,DirectX!!\n");

	return 0;
}