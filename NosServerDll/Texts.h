#pragma once
#include <string>
#include <vector>
#include "obfuscator.hpp"

class Texts
{
public:
	inline static std::string Ok;
	inline static std::string Fps;
	inline static std::string Rpc;
	inline static std::string IsLauncher;

	inline static std::string Fps_set;
	inline static std::string Prefix_send;
	inline static std::string Prefix_recv;
	inline static std::string Verify_inline;
	inline static std::string Fps_default;
	inline static std::string Copyright_after_life;

	inline static std::string Discord_image_key;
	inline static std::string Discord_logo_key;
	inline static std::string Discord_application_key;

	inline static std::vector<std::string> Module_list;

	static void Initialize (const std::string&);
};

inline void Texts::Initialize (const std::string& moduleName)
{
	Ok = OBFUSCATE("OK");
	Fps = OBFUSCATE("$FPS");
	Rpc = OBFUSCATE("$RPC");
	IsLauncher = OBFUSCATE("$IsLauncher");

	Fps_set = OBFUSCATE("msg 3 FPS  Set to ");
	Prefix_send = OBFUSCATE("[SEND] ");
	Prefix_recv = OBFUSCATE("[RECV] ");
	Verify_inline = OBFUSCATE("Verify ");
	Fps_default = OBFUSCATE("msg 3 FPS-Limit Set to default");
	Copyright_after_life = OBFUSCATE("msg 2 Anti-Packet by AfterLife#8695");

	Discord_image_key = OBFUSCATE("background");
	Discord_logo_key = OBFUSCATE("logo");
	Discord_application_key = OBFUSCATE("900077865134092368");

	Module_list = {moduleName, OBFUSCATE("crystalnos.exe"), OBFUSCATE("ninput.dll"), OBFUSCATE("atiu9pag.dll"), OBFUSCATE("atiumdag.dll"), OBFUSCATE("ntdll.dll"), OBFUSCATE("kernel32.dll"), OBFUSCATE("kernelbase.dll"), OBFUSCATE("apphelp.dll"), OBFUSCATE("acgenral.dll"), OBFUSCATE("msvcrt.dll"), OBFUSCATE("sechost.dll"), OBFUSCATE("rpcrt4.dll"), OBFUSCATE("shlwapi.dll"), OBFUSCATE("user32.dll"), OBFUSCATE("win32u.dll"), OBFUSCATE("gdi32.dll"), OBFUSCATE("gdi32full.dll"), OBFUSCATE("msvcp_win.dll"), OBFUSCATE("ucrtbase.dll"), OBFUSCATE("ole32.dll"), OBFUSCATE("combase.dll"), OBFUSCATE("oleaut32.dll"), OBFUSCATE("shell32.dll"), OBFUSCATE("advapi32.dll"), OBFUSCATE("uxtheme.dll"), OBFUSCATE("winmm.dll"), OBFUSCATE("samcli.dll"), OBFUSCATE("msacm32.dll"), OBFUSCATE("version.dll"), OBFUSCATE("userenv.dll"), OBFUSCATE("dwmapi.dll"), OBFUSCATE("urlmon.dll"), OBFUSCATE("winspool.drv"), OBFUSCATE("mpr.dll"), OBFUSCATE("sspicli.dll"), OBFUSCATE("winmmbase.dll"), OBFUSCATE("iertutil.dll"), OBFUSCATE("shcore.dll"), OBFUSCATE("srvcli.dll"), OBFUSCATE("netutils.dll"), OBFUSCATE("imm32.dll"), OBFUSCATE("comctl32.dll"), OBFUSCATE("d3d9.dll"), OBFUSCATE("steam_wrapper.dll"), OBFUSCATE("mss32.dll"), OBFUSCATE("gf_wrapper.dll"), OBFUSCATE("wsock32.dll"), OBFUSCATE("ws2_32.dll"), OBFUSCATE("kernel.appcore.dll"), OBFUSCATE("windows.storage.dll"), OBFUSCATE("steam_api.dll"), OBFUSCATE("psw_tnt.dll"), OBFUSCATE("psw_steam.dll"), OBFUSCATE("wldp.dll"), OBFUSCATE("gameforge_api.dll"), OBFUSCATE("ewdl.ews"), OBFUSCATE("msctf.dll"), OBFUSCATE("olepro32.dll"), OBFUSCATE("bcryptprimitives.dll"), OBFUSCATE("textinputframework.dll"), OBFUSCATE("coremessaging.dll"), OBFUSCATE("coreuicomponents.dll"), OBFUSCATE("ntmarta.dll"), OBFUSCATE("wintypes.dll"), OBFUSCATE("mssmp3.asi"), OBFUSCATE("mssogg.asi"), OBFUSCATE("mssvoice.asi"), OBFUSCATE("mssdolby.flt"), OBFUSCATE("mssds3d.flt"), OBFUSCATE("mssdsp.flt"), OBFUSCATE("msseax.flt"), OBFUSCATE("msssrs.flt"), OBFUSCATE("dsound.dll"), OBFUSCATE("powrprof.dll"), OBFUSCATE("umpdc.dll"), OBFUSCATE("clbcatq.dll"), OBFUSCATE("mmdevapi.dll"), OBFUSCATE("devobj.dll"), OBFUSCATE("cfgmgr32.dll"), OBFUSCATE("audioses.dll"), OBFUSCATE("resourcepolicyclient.dll"), OBFUSCATE("windows.ui.dll"), OBFUSCATE("inputhost.dll"), OBFUSCATE("windowmanagementapi.dll"), OBFUSCATE("propsys.dll"), OBFUSCATE("twinapi.appcore.dll"), OBFUSCATE("avrt.dll"), OBFUSCATE("nvldumd.dll"), OBFUSCATE("msasn1.dll"), OBFUSCATE("cryptnet.dll"), OBFUSCATE("crypt32.dll"), OBFUSCATE("drvstore.dll"), OBFUSCATE("cryptbase.dll"), OBFUSCATE("wintrust.dll"), OBFUSCATE("imagehlp.dll"), OBFUSCATE("cryptsp.dll"), OBFUSCATE("rsaenh.dll"), OBFUSCATE("bcrypt.dll"), OBFUSCATE("nvd3dum.dll"), OBFUSCATE("nvspcap.dll"), OBFUSCATE("profapi.dll"), OBFUSCATE("gpapi.dll"), OBFUSCATE("dxcore.dll"), OBFUSCATE("textshaping.dll"), OBFUSCATE("libcef.dll"), OBFUSCATE("psapi.dll"), OBFUSCATE("comdlg32.dll"), OBFUSCATE("wtsapi32.dll"), OBFUSCATE("dhcpcsvc.dll"), OBFUSCATE("winhttp.dll"), OBFUSCATE("secur32.dll"), OBFUSCATE("iphlpapi.dll"), OBFUSCATE("oleacc.dll"), OBFUSCATE("usp10.dll"), OBFUSCATE("dwrite.dll"), OBFUSCATE("nlaapi.dll"), OBFUSCATE("nsi.dll"), OBFUSCATE("dhcpcsvc6.dll"), OBFUSCATE("setupapi.dll"), OBFUSCATE("dnsapi.dll"), OBFUSCATE("d3dcompiler_47.dll"), OBFUSCATE("libglesv2.dll"), OBFUSCATE("libegl.dll"), OBFUSCATE("dxgi.dll"), OBFUSCATE("d3d11.dll"), OBFUSCATE("winsta.dll"), OBFUSCATE("dataexchange.dll"), OBFUSCATE("dcomp.dll"), OBFUSCATE("nvwgf2um.dll"), OBFUSCATE("vcruntime140.dll"), OBFUSCATE("msvcp140.dll"), OBFUSCATE("ucrtbased.dll"), OBFUSCATE("mswsock.dll"), OBFUSCATE("ewss.ews")};
}
