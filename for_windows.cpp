#include <natupnp.h>
#include <objbase.h>
#include <oleauto.h>
#include <winsock.h>
#include <string>
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib,"ole32.lib")
#pragma comment(lib,"oleaut32.lib")
int main() {
    CoInitialize(nullptr);//comの初期化
    IUPnPNAT* nat;
    CoCreateInstance(CLSID_UPnPNAT, nullptr, CLSCTX_ALL, IID_IUPnPNAT, reinterpret_cast<void**>(&nat));//インスタンスの取得
    IStaticPortMappingCollection* maps;
    nat->get_StaticPortMappingCollection(&maps);//ポートマッピングのリスト取得
    if (!maps)return 0;
    std::wstring ip(L"192.168.0.8");//マッピングしたいローカルアドレスを指定
    const auto localIp = SysAllocString(ip.c_str());
    const auto udp = SysAllocString(L"UDP");//UDP通信を指定 TCPの場合はTCPを指定する
    IStaticPortMapping* map;
    const auto name = SysAllocString(L"Test");//リストに登録される名前
    constexpr auto port = 49460;//マッピングしたIPのどのポートに送信されるか
    maps->Add(port, udp, port, localIp, VARIANT_TRUE, name, &map);//リストに登録
    system("pause");
    maps->Remove(port, udp);//リストから削除
    SysFreeString(name);
    SysFreeString(udp);
    SysFreeString(localIp);
    map->Release();
    maps->Release();
    nat->Release();
    CoUninitialize();//リソースの開放など
    return EXIT_SUCCESS;
}
