#include <natupnp.h>
#include <objbase.h>
#include <oleauto.h>
#include <winsock.h>
#include <string>
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib,"ole32.lib")
#pragma comment(lib,"oleaut32.lib")
int main() {
    CoInitialize(nullptr);//com�̏�����
    IUPnPNAT* nat;
    CoCreateInstance(CLSID_UPnPNAT, nullptr, CLSCTX_ALL, IID_IUPnPNAT, reinterpret_cast<void**>(&nat));//�C���X�^���X�̎擾
    IStaticPortMappingCollection* maps;
    nat->get_StaticPortMappingCollection(&maps);//�|�[�g�}�b�s���O�̃��X�g�擾
    if (!maps)return 0;
    std::wstring ip(L"192.168.0.8");//�}�b�s���O���������[�J���A�h���X���w��
    const auto localIp = SysAllocString(ip.c_str());
    const auto udp = SysAllocString(L"UDP");//UDP�ʐM���w�� TCP�̏ꍇ��TCP���w�肷��
    IStaticPortMapping* map;
    const auto name = SysAllocString(L"Test");//���X�g�ɓo�^����閼�O
    constexpr auto port = 49460;//�}�b�s���O����IP�̂ǂ̃|�[�g�ɑ��M����邩
    maps->Add(port, udp, port, localIp, VARIANT_TRUE, name, &map);//���X�g�ɓo�^
    system("pause");
    maps->Remove(port, udp);//���X�g����폜
    SysFreeString(name);
    SysFreeString(udp);
    SysFreeString(localIp);
    map->Release();
    maps->Release();
    nat->Release();
    CoUninitialize();//���\�[�X�̊J���Ȃ�
    return EXIT_SUCCESS;
}