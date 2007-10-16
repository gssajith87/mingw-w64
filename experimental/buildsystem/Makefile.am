# INCLUDES = -I$(top_srcdir) -I$(includedir)
# Done: lib_LIBRARIES = libm.a libmingw32.a libmoldname.a libmingwex.a libcrtdll.a libmsvcrt.a libmsvcr80.a
# TODO: Turn _libm_dummy.c into a BUILT_SOURCES thing

#Use AM_MAINTAINER_MODE in configure.ac to disable autoreconf

if WITHSYSROOT
  sysincludes=-I@TARGET_SYSTEM_ROOT@/mingw/include
else
  sysincludes=
endif

AM_CPPFLAGS=-D_CRTBLD -D_SYSCRT=1 -DCRTDLL=1 -DWINHEAP=1 $(sysincludes)
DLLOPTS=-k --as=$(AS) --output-lib $@

#######
# Dummy file for libm.a
BUILT_SOURCES = _libm_dummy.c
_libm_dummy.c:
	echo "static int __mingw_libm_dummy;" > _libm_dummy.c
#######

# These targets require special handling that automake can't
# yet support (or that I don't know how to do properly)
crtdir=$(prefix)/$(target)/lib
crt_SCRIPTS = \
  crt1.o crt2.o dllcrt1.o dllcrt2.o CRT_fp8.o CRT_fp10.o txtmode.o binmode.o crtbegin.o crtend.o \
  libcrtdll.a libmsvcrt.a libmsvcr80.a

crt1.o:
	$(COMPILE) -c $(top_srcdir)/crtexe.c -o $@ -D__CRTDLL__ -U__MSVCRT__
crt2.o:
	$(COMPILE) -c $(top_srcdir)/crtexe.c -o $@ -D__MSVCRT__ -U__CRTDLL__
dllcrt1.o:
	$(COMPILE) -c $(top_srcdir)/crtdll.c -o $@ -D__CRTDLL__ -U__MSVCRT__
dllcrt2.o:
	$(COMPILE) -c $(top_srcdir)/crtdll.c -o $@ -D__MSVCRT__ -U__CRTDLL__
libcrtdll.a libmsvcrt.a libmsvcr80.a:
	base=`echo $@ | sed -e 's/\.a//' -e 's/^lib//'`; \
	$(DLLTOOL) $(DLLOPTS) --dllname $${base}.dll --def $(top_srcdir)/$${base}.def
#libcrtdll.a:
#	$(DLLTOOL) --as=$(AS) -k --dllname crtdll.dll --output-lib $@ --def $(top_srcdir)/crtdll.def
#libmsvcrt.a:
#	$(DLLTOOL) --as=$(AS) -k --dllname msvcrt.dll --output-lib $@ --def $(top_srcdir)/msvcrt.def
#libmsvcr80.a:
#	$(DLLTOOL) --as=$(AS) -k --dllname msvcr80.dll --output-lib $@ --def $(top_srcdir)/msvcr80.def

crt_SCRIPTS += \
  lib6to4svc.a    libCINTIME.a    libCmdEvTgProv.a libPS5UI.a     libPSCRIPT5.a   libUNIDRV.a     \
  libUNIDRVUI.a   libaaaamon.a    libacgen64.a    libacledit.a    libaclui.a      libactiveds.a   \
  libactxprxy.a   libadmparse.a   libadmwprox.a   libadptif.a     libadrot.a      libadsiis.a     \
  libadsiisex.a   libadsldp.a     libadsldpc.a    libadsmsext.a   libadsnt.a      libadvapi32.a   \
  libadvpack.a    libaelupsvc.a   libagentanm.a   libagentctl.a   libagentdp2.a   libagentdpv.a   \
  libagentmpx.a   libagentpsh.a   libagentsr.a    libagrmco64.a   libagtintl.a    libakscoinst.a  \
  libalrsvc.a     libamstream.a   libapcups.a     libapphelp.a    libappmgmts.a   libappmgr.a     \
  libaqadmin.a    libaqueue.a     libasp.a        libaspperf.a    libasycfilt.a   libatkctrs.a    \
  libatl.a        libatmlib.a     libatmpvcno.a   libatrace.a     libaudiosrv.a   libauthz.a      \
  libautodisc.a   libavicap32.a   libavifil32.a   libazroles.a    libazroleui.a   libbasesrv.a    \
  libbatmeter.a   libbatt.a       libbidispl.a    libbitsprx2.a   libbitsprx3.a   libbnts.a       \
  libbootvid.a    libbrowscap.a   libbrowser.a    libbrowseui.a   libbrpinfo.a    libbthci.a      \
  libbthserv.a    libbtpanui.a    libc_g18030.a   libc_is2022.a   libc_iscii.a    libcabinet.a    \
  libcabview.a    libcamocx.a     libcards.a      libcatsrv.a     libcatsrvps.a   libcatsrvut.a   \
  libccfgnt.a     libcdfview.a    libcdm.a        libcdosys.a     libcertcli.a    libcertmgr.a    \
  libcertobj.a    libcfgbkend.a   libcfgmgr32.a   libchsbrkr.a    libchtbrkr.a    libchtskdic.a   \
  libchtskf.a     libciadmin.a    libcic.a        libcimwin32.a   libciodm.a      libclb.a        \
  libclbcatex.a   libclbcatq.a    libcliconfg.a   libclusapi.a    libcmcfg32.a    libcmdial32.a   \
  libcmpbk32.a    libcmprops.a    libcmsetacl.a   libcmutil.a     libcnbjmon.a    libcnetcfg.a    \
  libcnvfat.a     libcoadmin.a    libcolbact.a    libcomaddin.a   libcomadmin.a   libcomcat.a     \
  libcomctl32.a   libcomdlg32.a   libcompatui.a   libcompstui.a   libcomrepl.a    libcomres.a     \
  libcomsetup.a   libcomsnap.a    libcomsvcs.a    libcomuid.a     libconfmsp.a    libconsole.a    \
  libcontrot.a    libcorpol.a     libcredui.a     libcrypt32.a    libcryptdlg.a   libcryptdll.a   \
  libcryptext.a   libcryptnet.a   libcryptsvc.a   libcryptui.a    libcscdll.a     libcscui.a      \
  libcsrsrv.a     libd3d8thk.a    libd3d9.a       libd3dxof.a     libdanim.a      libdataclen.a   \
  libdatime.a     libdavclnt.a    libdavcprox.a   libdbgeng.a     libdbghelp.a    libdbnetlib.a   \
  libdbnmpntw.a   libdciman32.a   libddraw.a      libddrawex.a    libdeskadp.a    libdeskmon.a    \
  libdeskperf.a   libdevenum.a    libdevmgr.a     libdfrgifps.a   libdfrgsnap.a   libdfrgui.a     \
  libdfsshlex.a   libdgnet.a      libdhcpcsvc.a   libdhcpmon.a    libdhcpsapi.a   libdiactfrm.a   \
  libdigest.a     libdimap.a      libdimsntfy.a   libdimsroam.a   libdinput.a     libdinput8.a    \
  libdirectdb.a   libdiskcopy.a   libdispex.a     libdmconfig.a   libdmdlgs.a     libdmdskmgr.a   \
  libdmintf.a     libdmivcitf.a   libdmocx.a      libdmserver.a   libdmutil.a     libdmvdsitf.a   \
  libdnsapi.a     libdnsrslvr.a   libdocprop.a    libdocprop2.a   libdpnaddr.a    libdpnet.a      \
  libdpnhpast.a   libdpnhupnp.a   libdpnlobby.a   libdpvacm.a     libdpvoice.a    libdpvvox.a     \
  libdrprov.a     libds32gt.a     libdsauth.a     libdsdmo.a      libdsdmoprp.a   libdskquota.a   \
  libdskquoui.a   libdsound.a     libdsound3d.a   libdsprop.a     libdsprov.a     libdsquery.a    \
  libdssec.a      libdssenh.a     libdsuiext.a    libduser.a      libdxdiagn.a    libdxtmsft.a    \
  libdxtrans.a    libefsadu.a     libels.a        libencapi.a     libersvc.a      libes.a         \
  libesent.a      libesentprf.a   libesscli.a     libeventcls.a   libeventlog.a   libevntagnt.a   \
  libevntrprv.a   libevtgprov.a   libexstrace.a   libextmgr.a     libf3ahvoas.a   libfastprox.a   \
  libfaultrep.a   libfcachdll.a   libfde.a        libfdeploy.a    libfeclient.a   libfilemgmt.a   \
  libfldrclnr.a   libfltlib.a     libfmifs.a      libfontext.a    libfontsub.a    libframedyn.a   \
  libfsusd.a      libftpctrs2.a   libftpmib.a     libftpsvc2.a    libfwcfg.a      libfxsapi.a     \
  libfxscfgwz.a   libfxscom.a     libfxscomex.a   libfxsdrv.a     libfxsmon.a     libfxsocm.a     \
  libfxsperf.a    libfxsroute.a   libfxsst.a      libfxst30.a     libfxstiff.a    libfxsui.a      \
  libfxswzrd.a    libgcdef.a      libgdi32.a      libgetuname.a   libglmf32.a     libglu32.a      \
  libgpedit.a     libgpkcsp.a     libgptext.a     libguitrn.a     libgzip.a       libh323msp.a    \
  libhal.a        libhbaapi.a     libhgfs.a       libhhsetup.a    libhid.a        libhlink.a      \
  libhmmapi.a     libhnetcfg.a    libhnetmon.a    libhnetwiz.a    libhostmib.a    libhotplug.a    \
  libhticons.a    libhtrn_jis.a   libhttpapi.a    libhttpext.a    libhttpmib.a    libhttpodbc.a   \
  libhtui.a       libhypertrm.a   libiasacct.a    libiasads.a     libiashlpr.a    libiasnap.a     \
  libiaspolcy.a   libiasrad.a     libiassam.a     libiassdo.a     libiassvcs.a    libicaapi.a     \
  libicfgnt5.a    libicm32.a      libicmp.a       libicmui.a      libicwconn.a    libicwdial.a    \
  libicwdl.a      libicwhelp.a    libicwphbk.a    libicwutil.a    libidq.a        libieakeng.a    \
  libieaksie.a    libiedkcs32.a   libieencode.a   libiepeers.a    libiernonce.a   libiesetup.a    \
  libifmon.a      libifsutil.a    libigmpagnt.a   libiis.a        libiisadmin.a   libiiscfg.a     \
  libiisclex4.a   libiisext.a     libiislog.a     libiismap.a     libiisrstap.a   libiisrtl.a     \
  libiissuba.a    libiisui.a      libiisuiobj.a   libiisutil.a    libiisw3adm.a   libiiswmi.a     \
  libimagehlp.a   libimekrcic.a   libimepadsm.a   libimeshare.a   libimgutil.a    libimjp81k.a    \
  libimjpcic.a    libimjpcus.a    libimjpdct.a    libimjputyc.a   libimlang.a     libimm32.a      \
  libimsinsnt.a   libimskdic.a    libimskf.a      libinetcfg.a    libinetcomm.a   libinetmgr.a    \
  libinetmib1.a   libinetpp.a     libinetppui.a   libinfoadmn.a   libinfocomm.a   libinfoctrs.a   \
  libinfosoft.a   libinitpki.a    libinput.a      libinseng.a     libiphlpapi.a   libipmontr.a    \
  libipnathlp.a   libippromon.a   libiprip.a      libiprop.a      libiprtprio.a   libiprtrmgr.a   \
  libipsecsnp.a   libipsecsvc.a   libipsmsnap.a   libipv6mon.a    libipxsap.a     libirclass.a    \
  libisapips.a    libisatq.a      libiscomlog.a   libisign32.a    libitircl.a     libitss.a       \
  libixsso.a      libiyuv_32.a    libjet500.a     libjscript.a    libjsproxy.a    libkbd101.a     \
  libkbd101a.a    libkbd101b.a    libkbd101c.a    libkbd103.a     libkbd106.a     libkbd106n.a    \
  libkbda1.a      libkbda2.a      libkbda3.a      libkbdal.a      libkbdarme.a    libkbdarmw.a    \
  libkbdax2.a     libkbdaze.a     libkbdazel.a    libkbdbe.a      libkbdbene.a    libkbdblr.a     \
  libkbdbr.a      libkbdbu.a      libkbdca.a      libkbdcan.a     libkbdcr.a      libkbdcz.a      \
  libkbdcz1.a     libkbdcz2.a     libkbdda.a      libkbddiv1.a    libkbddiv2.a    libkbddv.a      \
  libkbdes.a      libkbdest.a     libkbdfa.a      libkbdfc.a      libkbdfi.a      libkbdfo.a      \
  libkbdfr.a      libkbdgae.a     libkbdgeo.a     libkbdgkl.a     libkbdgr.a      libkbdgr1.a     \
  libkbdhe.a      libkbdhe220.a   libkbdhe319.a   libkbdheb.a     libkbdhela2.a   libkbdhela3.a   \
  libkbdhept.a    libkbdhu.a      libkbdhu1.a     libkbdibm02.a   libkbdic.a      libkbdindev.a   \
  libkbdinguj.a   libkbdinhin.a   libkbdinkan.a   libkbdinmar.a   libkbdinpun.a   libkbdintam.a   \
  libkbdintel.a   libkbdir.a      libkbdit.a      libkbdit142.a   libkbdjpn.a     libkbdkaz.a     \
  libkbdkor.a     libkbdkyr.a     libkbdla.a      libkbdlk41a.a   libkbdlk41j.a   libkbdlt.a      \
  libkbdlt1.a     libkbdlv.a      libkbdlv1.a     libkbdmac.a     libkbdmon.a     libkbdne.a      \
  libkbdnec.a     libkbdnec95.a   libkbdnecat.a   libkbdnecnt.a   libkbdno.a      libkbdpl.a      \
  libkbdpl1.a     libkbdpo.a      libkbdro.a      libkbdru.a      libkbdru1.a     libkbdsf.a      \
  libkbdsg.a      libkbdsl.a      libkbdsl1.a     libkbdsp.a      libkbdsw.a      libkbdsyr1.a    \
  libkbdsyr2.a    libkbdtat.a     libkbdth0.a     libkbdth1.a     libkbdth2.a     libkbdth3.a     \
  libkbdtuf.a     libkbdtuq.a     libkbduk.a      libkbdur.a      libkbdurdu.a    libkbdus.a      \
  libkbdusa.a     libkbdusl.a     libkbdusr.a     libkbdusx.a     libkbduzb.a     libkbdvntc.a    \
  libkbdycc.a     libkbdycl.a     libkd1394.a     libkdcom.a      libkerberos.a   \
  libkeymgr.a     libkorwbrkr.a   libkrnlprov.a   libksuser.a     liblangwrbk.a   liblicdll.a     \
  liblicmgr10.a   liblicwmi.a     liblinkinfo.a   liblmhsvc.a     liblmmib2.a     liblmrt.a       \
  libloadperf.a   liblocalsec.a   liblocalspl.a   liblocalui.a    liblog.a        libloghours.a   \
  liblogscrpt.a   liblonsint.a    liblpdsvc.a     liblpk.a        liblprhelp.a    liblprmon.a     \
  liblprmonui.a   liblsasrv.a     liblz32.a       libmag_hook.a   libmailmsg.a    libmapi32.a     \
  libmapistub.a   libmcastmib.a   libmcd32.a      libmcdsrv32.a   libmchgrcoi.a   libmciavi32.a   \
  libmcicda.a     libmciole32.a   libmciqtz32.a   libmciseq.a     libmciwave.a    libmdhcp.a      \
  libmdminst.a    libmetadata.a   libmf3216.a     libmfc42.a      libmfc42u.a     libmfcsubs.a    \
  libmgmtapi.a    libmidimap.a    libmigism.a     libmiglibnt.a   libmimefilt.a   libmlang.a      \
  libmll_hp.a     libmll_mtf.a    libmll_qic.a    libmmcbase.a    libmmcndmgr.a   libmmcshext.a   \
  libmmfutil.a    libmmutilse.a   libmobsync.a    libmodemui.a    libmofd.a       libmpr.a        \
  libmprapi.a     libmprddm.a     libmprdim.a     libmprmsg.a     libmprui.a      libmqad.a       \
  libmqcertui.a   libmqdscli.a    libmqgentr.a    libmqise.a      libmqlogmgr.a   libmqoa.a       \
  libmqperf.a     libmqqm.a       libmqrt.a       libmqrtdep.a    libmqsec.a      libmqsnap.a     \
  libmqtrig.a     libmqupgrd.a    libmqutil.a     libmsaatext.a   libmsacm32.a    libmsadce.a     \
  libmsadcf.a     libmsadco.a     libmsadcs.a     libmsadds.a     libmsado15.a    libmsadomd.a    \
  libmsador15.a   libmsadox.a     libmsadrh15.a   libmsafd.a      libmsasn1.a     libmscandui.a   \
  libmscat32.a    libmscms.a      libmsctf.a      libmsctfp.a     libmsdadiag.a   libmsdaosp.a    \
  libmsdaprst.a   libmsdaps.a     libmsdarem.a    libmsdart.a     libmsdatl3.a    libmsdfmap.a    \
  libmsdmo.a      libmsdtclog.a   libmsdtcprx.a   libmsdtcstp.a   libmsdtctm.a    libmsdtcuiu.a   \
  libmsftedit.a   libmsgina.a     libmsgr3en.a    libmsgrocm.a    libmsgsvc.a     libmshtml.a     \
  libmshtmled.a   libmsi.a        libmsident.a    libmsieftp.a    libmsihnd.a     libmsimg32.a    \
  libmsimtf.a     libmsinfo.a     libmsiprov.a    libmsir3jp.a    libmsisip.a     libmslbui.a     \
  libmsls31.a     libmslwvtts.a   libmsmqocm.a    libmsobcomm.a   libmsobdl.a     libmsobmain.a   \
  libmsobshel.a   libmsobweb.a    libmsoe.a       libmsoeacct.a   libmsoert2.a    libmspatcha.a   \
  libmspmsnsv.a   libmsports.a    libmsrating.a   libmsrle32.a    libmssign32.a   libmssip32.a    \
  libmstask.a     libmstime.a     libmstlsapi.a   libmstscax.a    libmsutb.a      libmsv1_0.a     \
  libmsvcirt.a    libmsvcp60.a    libmsvfw32.a    libmsvidc32.a   libmsvidctl.a   libmsw3prt.a    \
  libmswsock.a    libmsxactps.a   libmsxml3.a     libmsxs64.a     libmsyuv.a      libmtxclu.a     \
  libmtxdm.a      libmtxex.a      libmtxoci.a     libmycomput.a   libmydocs.a     libnarrhook.a   \
  libncobjapi.a   libncprov.a     libncxpnt.a     libnddeapi.a    libnddenb32.a   libndisnpp.a    \
  libnetapi32.a   libnetcfgx.a    libnetid.a      libnetlogon.a   libnetman.a     libnetoc.a      \
  libnetplwiz.a   libnetrap.a     libnetshell.a   libnetui0.a     libnetui1.a     libnetui2.a     \
  libnewdev.a     libnextlink.a   libnlhtml.a     libnntpadm.a    libnntpapi.a    libnntpsnap.a   \
  libnpptools.a   libnshipsec.a   libntdll.a      libntdsapi.a    libntdsbcli.a   libntevt.a      \
  libntfsdrv.a    libntlanman.a   libntlanui.a    libntlanui2.a   libntlsapi.a    libntmarta.a    \
  libntmsapi.a    libntmsdba.a    libntmsevt.a    libntmsmgr.a    libntmssvc.a    libntoc.a       \
  libntprint.a    libntshrui.a    libntvdm64.a    libnwprovau.a   liboakley.a     libobjsel.a     \
  liboccache.a    libocgen.a      libocmanage.a   libocmsn.a      libodbc32.a     libodbc32gt.a   \
  libodbcbcp.a    libodbcconf.a   libodbccp32.a   libodbccr32.a   libodbccu32.a   libodbctrac.a   \
  liboeimport.a   liboemiglib.a   libofffilt.a    libole32.a      liboleacc.a     liboleaut32.a   \
  libolecli32.a   libolecnv32.a   liboledb32.a    liboledb32r.a   liboledlg.a     liboleprn.a     \
  libolesvr32.a   libopengl32.a   libosuninst.a   libovprintmondll.a libpadrs404.a   libpadrs411.a   \
  libpadrs412.a   libpadrs804.a   libpanmap.a     libpautoenr.a   libpchshell.a   libpchsvc.a     \
  libpdh.a        libperfctrs.a   libperfdisk.a   libperfnet.a    libperfos.a     libperfproc.a   \
  libperfts.a     libphotowiz.a   libpid.a        libpidgen.a     libpintlcsa.a   libpintlcsd.a   \
  libpjlmon.a     libpngfilt.a    libpolicman.a   libpolstore.a   libpowrprof.a   libprintui.a    \
  libprofmap.a    libprovthrd.a   libpsapi.a      libpsbase.a     libpschdprf.a   libpsnppagn.a   \
  libpstorec.a    libpstorsvc.a   libqasf.a       libqcap.a       libqdv.a        libqdvd.a       \
  libqedit.a      libqmgr.a       libqmgrprxy.a   libqosname.a    libquartz.a     libquery.a      \
  libracpldlg.a   librasadhlp.a   librasapi32.a   librasauto.a    libraschap.a    librasctrs.a    \
  librasdlg.a     librasman.a     librasmans.a    librasmontr.a   librasmxs.a     librasppp.a     \
  librasrad.a     librassapi.a    librasser.a     librastapi.a    librastls.a     librcbdyctl.a   \
  librdchost.a    librdpcfgex.a   librdpsnd.a     librdpwsx.a     libregapi.a     libregsvc.a     \
  libregwizc.a    libremotepg.a   librend.a       librepdrvfs.a   libresutils.a   libriched20.a   \
  librnr20.a      libroutetab.a   librpcns4.a     librpcnsh.a     librpcref.a     librpcrt4.a     \
  librpcss.a      librsaenh.a     librsfsaps.a    librshx32.a     librsmps.a      librtm.a        \
  librtutils.a    librwnh.a       libsafrcdlg.a   libsafrdm.a     libsafrslv.a    libsamlib.a     \
  libsamsrv.a     libsapi.a       libscarddlg.a   libsccbase.a    libsccsccp.a    libscecli.a     \
  libscesrv.a     libschannel.a   libschedsvc.a   libsclgntfy.a   libscredir.a    libscript.a     \
  libscripto.a    libscriptpw.a   libscrobj.a     libscrptutl.a   libscrrun.a     libsdhcinst.a   \
  libsdpblb.a     libseclogon.a   libsecur32.a    libsecurity.a   libsendcmsg.a   libsendmail.a   \
  libsens.a       libsensapi.a    libsenscfg.a    libseo.a        libseos.a       libserialui.a   \
  libservdeps.a   libserwvdrv.a   libsetupapi.a   libsetupqry.a   libsfc.a        libsfc_os.a     \
  libsfcfiles.a   libsfmapi.a     libshdocvw.a    libshfolder.a   libshgina.a     \
  libshimeng.a    libshimgvw.a    libshlwapi.a    libshmedia.a    libshscrap.a    libshsvcs.a     \
  libsigtab.a     libsimptcp.a    libsisbkup.a    libskdll.a      libslayerxp.a   libslbcsp.a     \
  libslbiop.a     libsmlogcfg.a   libsmtpadm.a    libsmtpapi.a    libsmtpcons.a   libsmtpctrs.a   \
  libsmtpsnap.a   libsmtpsvc.a    libsniffpol.a   libsnmpapi.a    libsnmpcl.a     libsnmpincl.a   \
  libsnmpmib.a    libsnmpsmir.a   libsnmpsnap.a   libsnmpstup.a   libsnmpthrd.a   libsnprfdll.a   \
  libsoftkbd.a    libsoftkey.a    libsoftpub.a    libspcommon.a   libspoolss.a    libsptip.a      \
  libspttseng.a   libsqlsrv32.a   libsqlxmlx.a    libsrchctls.a   libsrchui.a     libsrclient.a   \
  libsrrstr.a     libsrsvc.a      libsrvsvc.a     libssdpapi.a    libssdpsrv.a    libssinc.a      \
  libsstub.a      libstaxmem.a    libstclient.a   libstdprov.a    libsti.a        libsti_ci.a     \
  libstobject.a   libstorprop.a   libstreamci.a   libstrmfilt.a   libsvcext.a     libsvcpack.a    \
  libswprv.a      libsxs.a        libsynceng.a    libsyncui.a     libsysinv.a     libsysmod.a     \
  libsyssetup.a   libt2embed.a    libtapi3.a      libtapi32.a     libtapiperf.a   libtapisrv.a    \
  libtcpmib.a     libtcpmon.a     libtcpmonui.a   libtermmgr.a    libtermsrv.a    libthawbrkr.a   \
  libthemeui.a    libtlntsvrp.a   libtraffic.a    libtrialoc.a    libtrkwks.a     libtsappcmp.a   \
  libtsbyuv.a     libtscfgwmi.a   libtsd32.a      libtshoot.a     libtsoc.a       libtwext.a      \
  libtxflog.a     libudhisapi.a   libufat.a       libuihelper.a   libulib.a       libumandlg.a    \
  libumdmxfrm.a   libumpnpmgr.a   libuniime.a     libunimdmat.a   libuniplat.a    libuntfs.a      \
  libupnp.a       libupnphost.a   libupnpui.a     libureg.a       liburl.a        liburlauth.a    \
  liburlmon.a     libusbmon.a     libuser32.a     libuserenv.a    libusp10.a      libutildll.a    \
  libuxtheme.a    libvbscript.a   libvds_ps.a     libvdsbas.a     libvdsdyndr.a   libvdsutil.a    \
  libvdswmi.a     libverifier.a   libversion.a    libvgx.a        libviewprov.a   libvmx_mode.a   \
  libvss_ps.a     libvssapi.a     libvsswmi.a     libw32time.a    libw32topl.a    libw3cache.a    \
  libw3comlog.a   libw3core.a     libw3ctrlps.a   libw3ctrs.a     libw3dt.a       libw3ext.a      \
  libw3isapi.a    libw3ssl.a      libw3tp.a       libwADROT.a     libwAcLayers.a  libwAcLua.a     \
  libwAcSpecfc.a  libwAcXtrnal.a  libwCHTSKDIC.a  libwCHTSKF.a    libwCINTIME.a   libwCmnclim.a   \
  libwContRot.a   libwHMMAPI.a    libwKBDAL.a     libwMSCTF.a     libwMSCTFP.a    libwMSIMTF.a    \
  libwNEXTLINK.a  libwPADRS404.a  libwPINTLCSA.a  libwPINTLCSD.a  libwaaaamon.a   libwab32.a      \
  libwabfind.a    libwabimp.a     libwacledit.a   libwaclui.a     libwactiveds.a  libwactxprxy.a  \
  libwacwow64.a   libwadmparse.a  libwadmwprx.a   libwadptif.a    libwadsiis.a    libwadsldp.a    \
  libwadsldpc.a   libwadsmsext.a  libwadsnt.a     libwadvapi32.a  libwadvpack.a   libwaelupsvc.a  \
  libwagentanm.a  libwagentctl.a  libwagentdp2.a  libwagentdpv.a  libwagentmpx.a  libwagentpsh.a  \
  libwagentsr.a   libwagtintl.a   libwair300pp.a  libwam.a        libwamps.a      libwamreg.a     \
  libwamregps.a   libwamstream.a  libwapcups.a    libwapphelp.a   libwappmgmts.a  libwappmgr.a    \
  libwasp.a       libwaspperf.a   libwasycfilt.a  libwatkctrs.a   libwatl.a       libwatmlib.a    \
  libwatmpvcno.a  libwaudiodev.a  libwaudiosrv.a  libwauthz.a     libwautodisc.a  libwavemsp.a    \
  libwavicap32.a  libwavifil32.a  libwavmcoxp.a   libwazroles.a   libwazroleui.a  libwbatmeter.a  \
  libwbatt.a      libwbckg.a      libwbckgres.a   libwbemcntl.a   libwbemcomn.a   libwbemcons.a   \
  libwbemcore.a   libwbemdisp.a   libwbemess.a    libwbemperf.a   libwbemprox.a   libwbemsvc.a    \
  libwbemupgd.a   libwbidispl.a   libwbitsprx2.a  libwbitsprx3.a  libwblackbox.a  libwbrowscap.a  \
  libwbrowser.a   libwbrowseui.a  libwbrowsewm.a  libwc_eucdb.a   libwc_g18030.a  libwc_is2022.a  \
  libwc_iscii.a   libwc_snadb.a   libwcabinet.a   libwcabview.a   libwcamocx.a    libwcards.a     \
  libwcatsrv.a    libwcatsrvps.a  libwcatsrvut.a  libwccfgnt.a    libwcdfview.a   libwcdosys.a    \
  libwcertcli.a   libwcertmgr.a   libwcertobj.a   libwcewmdm.a    libwcfgmgr32.a  libwchkr.a      \
  libwchsbrkr.a   libwchtbrkr.a   libwciadmin.a   libwcic.a       libwciodm.a     libwclb.a       \
  libwclbcatex.a  libwclbcatq.a   libwclusapi.a   libwcmcfg32.a   libwcmdial32.a  libwcmpbk32.a   \
  libwcmsetACL.a  libwcmutil.a    libwcnbjmon.a   libwcnetcfg.a   libwcnvfat.a    libwcolbact.a   \
  libwcomaddin.a  libwcomadmin.a  libwcomcat.a    libwcomctl32.a  libwcomdlg32.a  libwcompatUI.a  \
  libwcompstui.a  libwcomres.a    libwcomsnap.a   libwcomsvcs.a   libwcomuid.a    libwconfmsp.a   \
  libwconsole.a   libwcorpol.a    libwcredui.a    libwcrtdll.a    libwcrypt32.a   libwcryptdlg.a  \
  libwcryptdll.a  libwcryptext.a  libwcryptnet.a  libwcryptsvc.a  libwcryptui.a   libwcsapi3t1.a  \
  libwcscdll.a    libwcscui.a     libwcsseqchk.a  libwctl3d32.a   libwcustsat.a   libwcyycoins.a  \
  libwcyyports.a  libwcyzcoins.a  libwcyzports.a  libwd3d8.a      libwd3d8thk.a   libwd3d9.a      \
  libwd3dim.a     libwd3dim700.a  libwd3dpmesh.a  libwd3dramp.a   libwd3drm.a     libwd3dxof.a    \
  libwdanim.a     libwdao360.a    libwdataclen.a  libwdatime.a    libwdavclnt.a   libwdavcprox.a  \
  libwdbgeng.a    libwdbghelp.a   libwdbnetlib.a  libwdciman32.a  libwddraw.a     libwddrawex.a   \
  libwdeskadp.a   libwdeskmon.a   libwdeskperf.a  libwdevenum.a   libwdfsshlex.a  libwdgconfig.a  \
  libwdgnet.a     libwdgsetup.a   libwdhcpcsvc.a  libwdhcpmon.a   libwdhcpsapi.a  libwdiactfrm.a  \
  libwdigest.a    libwdigiinf.a   libwdigirlpt.a  libwdimap.a     libwdimsntfy.a  libwdimsroam.a  \
  libwdinput.a    libwdinput8.a   libwdirectdb.a  libwdiskcopy.a  libwdispex.a    libwdisrvci.a   \
  libwdmband.a    libwdmcompos.a  libwdmime.a     libwdmloader.a  libwdmocx.a     libwdmscript.a  \
  libwdmstyle.a   libwdmsynth.a   libwdmusic.a    libwdnsapi.a    libwdnsrslvr.a  libwdocprop.a   \
  libwdocprop2.a  libwdplay.a     libwdplayx.a    libwdpmodemx.a  libwdpnaddr.a   libwdpnet.a     \
  libwdpnhpast.a  libwdpnhupnp.a  libwdpnlobby.a  libwdpvacm.a    libwdpvoice.a   libwdpvvox.a    \
  libwdpwsockx.a  libwdrmclien.a  libwdrmstor.a   libwdrmv2clt.a  libwdrprov.a    libwds32gt.a    \
  libwdsauth.a    libwdsdmo.a     libwdsdmoprp.a  libwdskquota.a  libwdskquoui.a  libwdsound.a    \
  libwdsound3d.a  libwdsprop.a    libwdsquery.a   libwdssec.a     libwdssenh.a    libwdsuiext.a   \
  libwdswave.a    libwduser.a     libwdx7vb.a     libwdx8vb.a     libwdxdiagn.a   libwdxmasf.a    \
  libwdxtmsft.a   libwdxtrans.a   libwebcheck.a   libwebclnt.a    libwebhits.a    libwebvw.a      \
  libwedb500.a    libwefsadu.a    libwels.a       libwencapi.a    libwencdec.a    libwes.a        \
  libwesent.a     libwesent97.a   libwesentprf.a  libwesscli.a    libwevntrprv.a  libwevtgprov.a  \
  libwexpsrv.a    libwexstrace.a  libwextmgr.a    libwf3ahvoas.a  libwfastprox.a  libwfaultrep.a  \
  libwfde.a       libwfdeploy.a   libwfeclient.a  libwfilemgmt.a  libwfldrclnr.a  libwfltlib.a    \
  libwfmifs.a     libwfontext.a   libwfontsub.a   libwframedyn.a  libwfsusd.a     libwftlx041e.a  \
  libwftpctrs2.a  libwftsrch.a    libwfwcfg.a     libwfxsapi.a    libwfxscom.a    libwfxscomex.a  \
  libwfxsext32.a  libwfxsperf.a   libwfxsxp32.a   libwgcdef.a     libwgdi32.a     libwgetuname.a  \
  libwglmf32.a    libwglu32.a     libwgpedit.a    libwgpkcsp.a    libwgptext.a    libwguitrn.a    \
  libwguitrna.a   libwgzip.a      libwh323msp.a   libwhbaapi.a    libwhccoin.a    libwhhsetup.a   \
  libwhid.a       libwhidserv.a   libwhlink.a     libwhnetcfg.a   libwhnetmon.a   libwhrtz.a      \
  libwhsf_inst.a  libwhttpapi.a   libwhttpext.a   libwhttpmib.a   libwhttpodbc.a  libwhtui.a      \
  libwiadefui.a   libwiadss.a     libwiarpc.a     libwiasacct.a   libwiasads.a    libwiascr.a     \
  libwiaservc.a   libwiashext.a   libwiashlpr.a   libwiasnap.a    libwiaspolcy.a  libwiasrad.a    \
  libwiasrecst.a  libwiassam.a    libwiassdo.a    libwiassvcs.a   libwiavideo.a   libwiavusd.a    \
  libwicfgnt5.a   libwicm32.a     libwicmp.a      libwicmui.a     libwiconf32.a   libwicwconn.a   \
  libwicwdial.a   libwicwdl.a     libwicwhelp.a   libwicwphbk.a   libwicwutil.a   libwidq.a       \
  libwieakeng.a   libwieaksie.a   libwiedkcs32.a  libwieencode.a  libwiepeers.a   libwiernonce.a  \
  libwiesetup.a   libwifmon.a     libwifsutil.a   libwigmpagnt.a  libwiisext.a    libwiislog.a    \
  libwiismap.a    libwiispwchg.a  libwiisrstap.a  libwiisrtl.a    libwiisui.a     libwiisuiobj.a  \
  libwiisutil.a   libwiisw3adm.a  libwimagehlp.a  libwimekrcic.a  libwimepadsm.a  libwimeshare.a  \
  libwimgutil.a   libwimjp81k.a   libwimjpcic.a   libwimjpcus.a   libwimjpdct.a   libwimjputyc.a  \
  libwimlang.a    libwimm32.a     libwimskdic.a   libwimskf.a     libwin32spl.a   libwinetcfg.a   \
  libwinetcomm.a  libwinetmgr.a   libwinetmib1.a  libwinetpp.a    libwinetppui.a  libwinfax.a     \
  libwinfoadmn.a  libwinfoctrs.a  libwinfosoft.a  libwininet.a    libwinipsec.a   libwinitpki.a   \
  libwinmm.a      libwinntbbu.a   libwinput.a     libwinrnr.a     libwinscard.a   libwinseng.a    \
  libwinsrv.a     libwinsta.a     libwintrust.a   libwiphlpapi.a  libwipmontr.a   libwipnathlp.a  \
  libwippromon.a  libwiprip.a     libwiprop.a     libwiprtprio.a  libwiprtrmgr.a  libwipsecsnp.a  \
  libwipsecsvc.a  libwipsmsnap.a  libwipv6mon.a   libwipxsap.a    libwir41_qc.a   libwir41_qcx.a  \
  libwir50_32.a   libwir50_qc.a   libwir50_qcx.a  libwisapips.a   libwiscomlog.a  libwisign32.a   \
  libwitircl.a    libwitss.a      libwixsso.a     libwiyuv_32.a   libwjet500.a    libwjobexec.a   \
  libwjscript.a   libwjsproxy.a   libwkbd101.a    libwkbd101a.a   libwkbd101b.a   libwkbd101c.a   \
  libwkbd103.a    libwkbd106.a    libwkbd106n.a   libwkbda1.a     libwkbda2.a     libwkbda3.a     \
  libwkbdarme.a   libwkbdarmw.a   libwkbdax2.a    libwkbdaze.a    libwkbdazel.a   libwkbdbe.a     \
  libwkbdbene.a   libwkbdblr.a    libwkbdbr.a     libwkbdbu.a     libwkbdca.a     libwkbdcan.a    \
  libwkbdcr.a     libwkbdcz.a     libwkbdcz1.a    libwkbdcz2.a    libwkbdda.a     libwkbddiv1.a   \
  libwkbddiv2.a   libwkbddv.a     libwkbdes.a     libwkbdest.a    libwkbdfa.a     libwkbdfc.a     \
  libwkbdfi.a     libwkbdfo.a     libwkbdfr.a     libwkbdgae.a    libwkbdgeo.a    libwkbdgkl.a    \
  libwkbdgr.a     libwkbdgr1.a    libwkbdhe.a     libwkbdhe220.a  libwkbdhe319.a  libwkbdheb.a    \
  libwkbdhela2.a  libwkbdhela3.a  libwkbdhept.a   libwkbdhu.a     libwkbdhu1.a    libwkbdibm02.a  \
  libwkbdic.a     libwkbdindev.a  libwkbdinguj.a  libwkbdinhin.a  libwkbdinkan.a  libwkbdinmar.a  \
  libwkbdinpun.a  libwkbdintam.a  libwkbdintel.a  libwkbdir.a     libwkbdit.a     libwkbdit142.a  \
  libwkbdjpn.a    libwkbdkaz.a    libwkbdkor.a    libwkbdkyr.a    libwkbdla.a     libwkbdlk41a.a  \
  libwkbdlk41j.a  libwkbdlt.a     libwkbdlt1.a    libwkbdlv.a     libwkbdlv1.a    libwkbdmac.a    \
  libwkbdmon.a    libwkbdne.a     libwkbdnec.a    libwkbdnec95.a  libwkbdnecAT.a  libwkbdnecNT.a  \
  libwkbdno.a     libwkbdpl.a     libwkbdpl1.a    libwkbdpo.a     libwkbdro.a     libwkbdru.a     \
  libwkbdru1.a    libwkbdsf.a     libwkbdsg.a     libwkbdsl.a     libwkbdsl1.a    libwkbdsp.a     \
  libwkbdsw.a     libwkbdsyr1.a   libwkbdsyr2.a   libwkbdtat.a    libwkbdth0.a    libwkbdth1.a    \
  libwkbdth2.a    libwkbdth3.a    libwkbdtuf.a    libwkbdtuq.a    libwkbduk.a     libwkbdur.a     \
  libwkbdurdu.a   libwkbdus.a     libwkbdusa.a    libwkbdusl.a    libwkbdusr.a    libwkbdusx.a    \
  libwkbduzb.a    libwkbdvntc.a   libwkbdycc.a    libwkbdycl.a    libwkerberos.a  libwkernel32.a  \
  libwkeymgr.a    libwkorwbrkr.a  libwkssvc.a     libwksuser.a    libwlangwrbk.a  libwlanmon.a    \
  libwlaprxy.a    libwldap32.a    libwlicmgr10.a  libwlinkinfo.a  libwlmhsvc.a    libwlmmib2.a    \
  libwlmrt.a      libwlnotify.a   libwloadperf.a  libwlocalsec.a  libwlocalui.a   libwlog.a       \
  libwloghours.a  libwlogscrpt.a  libwlonsint.a   libwlpdsvc.a    libwlpk.a       libwlprhelp.a   \
  libwlprmon.a    libwlprmonui.a  libwlsnp.a      libwlstore.a    libwlz32.a      libwmag_hook.a  \
  libwmcastmib.a  libwmcd32.a     libwmchgrcoi.a  libwmciavi32.a  libwmcicda.a    libwmciole32.a  \
  libwmciqtz32.a  libwmciseq.a    libwmciwave.a   libwmdhcp.a     libwmdminst.a   libwmf3216.a    \
  libwmfc40.a     libwmfc40u.a    libwmfc42.a     libwmfc42u.a    libwmfcsubs.a   libwmgmtapi.a   \
  libwmi.a        libwmi2xml.a    libwmiaprpl.a   libwmicookr.a   libwmidcprv.a   libwmidimap.a   \
  libwmigism.a    libwmigisma.a   libwmiglibnt.a  libwmimefilt.a  libwmipcima.a   libwmipdskq.a   \
  libwmipicmp.a   libwmipiprt.a   libwmipjobj.a   libwmiprop.a    libwmiprov.a    libwmiprvsd.a   \
  libwmipsess.a   libwmiscmgr.a   libwmisvc.a     libwmitimep.a   libwmiutils.a   libwmlang.a     \
  libwmll_hp.a    libwmll_mtf.a   libwmll_qic.a   libwmmcbase.a   libwmmcndmgr.a  libwmmcshext.a  \
  libwmmfutil.a   libwmmutilse.a  libwmobsync.a   libwmodemui.a   libwmofd.a      libwmp43dmod.a  \
  libwmp4sdmod.a  libwmpg4dmod.a  libwmpr.a       libwmprapi.a    libwmprddm.a    libwmprdim.a    \
  libwmprmsg.a    libwmprui.a     libwmpshell.a   libwmpvis.a     libwmqad.a      libwmqdscli.a   \
  libwmqoa.a      libwmqperf.a    libwmqrt.a      libwmqsec.a     libwmqutil.a    libwmsaatext.a  \
  libwmsacm32.a   libwmsadce.a    libwmsadcf.a    libwmsadco.a    libwmsadcs.a    libwmsadds.a    \
  libwmsado15.a   libwmsadomd.a   libwmsador15.a  libwmsadox.a    libwmsadrh15.a  libwmsafd.a     \
  libwmsapsspc.a  libwmsasn1.a    libwmscandui.a  libwmscat32.a   libwmscms.a     libwmscpxl32.a  \
  libwmsdadc.a    libwmsdadiag.a  libwmsdaenum.a  libwmsdaer.a    libwmsdaora.a   libwmsdaosp.a   \
  libwmsdaprst.a  libwmsdaps.a    libwmsdarem.a   libwmsdart.a    libwmsdasc.a    libwmsdasql.a   \
  libwmsdatl3.a   libwmsdatt.a    libwmsdaurl.a   libwmsdfmap.a   libwmsdmo.a     libwmsdtcprx.a  \
  libwmsdtcuiu.a  libwmsexch40.a  libwmsexcl40.a  libwmsftedit.a  libwmsgina.a    libwmsgr3en.a   \
  libwmshtml.a    libwmshtmled.a  libwmsi.a       libwmsident.a   libwmsieftp.a   libwmsihnd.a    \
  libwmsimg32.a   libwmsir3jp.a   libwmsisip.a    libwmsjet40.a   libwmsjetol1.a  libwmsjint40.a  \
  libwmsjro.a     libwmsjter40.a  libwmsjtes40.a  libwmslbui.a    libwmsls31.a    libwmsltus40.a  \
  libwmslwvtts.a  libwmsnetobj.a  libwmsnsspc.a   libwmsoe.a      libwmsoeacct.a  libwmsoert2.a   \
  libwmsorcl32.a  libwmspatcha.a  libwmspbde40.a  libwmspmsnsv.a  libwmspmsp.a    libwmsports.a   \
  libwmsr2c.a     libwmsrating.a  libwmsrd2x40.a  libwmsrd3x40.a  libwmsrle32.a   libwmssap.a     \
  libwmsscp.a     libwmssign32.a  libwmssip32.a   libwmstask.a    libwmstext40.a  libwmstime.a    \
  libwmstlsapi.a  libwmstscax.a   libwmsutb.a     libwmsv1_0.a    libwmsvcirt.a   libwmsvcp50.a   \
  libwmsvcp60.a   libwmsvcrt.a    libwmsvcrt20.a  libwmsvcrt40.a  libwmsvfw32.a   libwmsvidc32.a  \
  libwmsvidctl.a  libwmsw3prt.a   libwmswebdvd.a  libwmswmdm.a    libwmswsock.a   libwmsxactps.a  \
  libwmsxbde40.a  libwmsxml.a     libwmsxml2.a    libwmsxml3.a    libwmsyuv.a     libwmtxclu.a    \
  libwmtxdm.a     libwmtxex.a     libwmtxlegih.a  libwmtxoci.a    libwmxicfg.a    libwmxport.a    \
  libwmycomput.a  libwmydocs.a    libwnarrhook.a  libwncobjapi.a  libwnddeapi.a   libwnddenb32.a  \
  libwnetapi32.a  libwnetcfgx.a   libwnetid.a     libwnetlogon.a  libwnetman.a    libwnetplwiz.a  \
  libwnetrap.a    libwnetshell.a  libwnetui0.a    libwnetui1.a    libwnetui2.a    libwnewdev.a    \
  libwnlhtml.a    libwnntpadm.a   libwnntpapi.a   libwnntpsnap.a  libwnpdsplay.a  libwnpptools.a  \
  libwnshipsec.a  libwntdll.a     libwntdsapi.a   libwntdsbcli.a  libwntlanman.a  libwntlanui.a   \
  libwntlanui2.a  libwntlsapi.a   libwntmarta.a   libwntmsapi.a   libwntprint.a   libwntshrui.a   \
  libwntvdm64.a   libwoakley.a    libwobjsel.a    libwoccache.a   libwocmanage.a  libwodbc32.a    \
  libwodbc32gt.a  libwodbcconf.a  libwodbccp32.a  libwodbccr32.a  libwodbccu32.a  libwodbcji32.a  \
  libwodbcjt32.a  libwodbctrac.a  libwoddbse32.a  libwodexl32.a   libwodfox32.a   libwodpdx32.a   \
  libwodtext32.a  libwoeimport.a  libwoemiglib.a  libwofffilt.a   libwole32.a     libwoleacc.a    \
  libwoleaut32.a  libwolecli32.a  libwolecnv32.a  libwoledb32.a   libwoledb32r.a  libwoledlg.a    \
  libwoleprn.a    libwolepro32.a  libwolesvr32.a  libwolethk32.a  libwopengl32.a  libwosuninst.a  \
  libwow64.a      libwow64cpu.a   libwow64mib.a   libwow64win.a   libwpadrs411.a  libwpadrs412.a  \
  libwpadrs804.a  libwpanmap.a    libwpautoenr.a  libwpd_ci.a     libwpdh.a       libwperfctrs.a  \
  libwperfdisk.a  libwperfnet.a   libwperfos.a    libwperfproc.a  libwperfts.a    libwphotowiz.a  \
  libwpid.a       libwpidgen.a    libwpjlmon.a    libwpngfilt.a   libwpolstore.a  libwpowrprof.a  \
  libwprintui.a   libwprofmap.a   libwprovthrd.a  libwpsapi.a     libwpsbase.a    libwpschdprf.a  \
  libwpsnppagn.a  libwpstorec.a   libwpstorsvc.a  libwqasf.a      libwqcap.a      libwqdv.a       \
  libwqdvd.a      libwqedit.a     libwqmgrprxy.a  libwqosname.a   libwquartz.a    libwquery.a     \
  libwrasadhlp.a  libwrasapi32.a  libwrasauto.a   libwraschap.a   libwrasctrs.a   libwrasdlg.a    \
  libwrasman.a    libwrasmans.a   libwrasmontr.a  libwrasmxs.a    libwrasppp.a    libwrasrad.a    \
  libwrassapi.a   libwrasser.a    libwrastapi.a   libwrastls.a    libwrdpsnd.a    libwregapi.a    \
  libwregsvc.a    libwregwizc.a   libwrend.a      libwresutils.a  libwriched20.a  libwrnr20.a     \
  libwroutetab.a  libwrpcns4.a    libwrpcnsh.a    libwrpcref.a    libwrpcrt4.a    libwrsaenh.a    \
  libwrshx32.a    libwrtm.a       libwrtutils.a   libwrvse.a      libwrwnh.a      libws2_32.a     \
  libws2help.a    libwsamlib.a    libwsapi.a      libwsbe.a       libwsbeio.a     libwscarddlg.a  \
  libwsccbase.a   libwsccsccp.a   libwscecli.a    libwschannel.a  libwschedsvc.a  libwsclgntfy.a  \
  libwscredir.a   libwscript.a    libwscripta.a   libwscripto.a   libwscriptpw.a  libwscrobj.a    \
  libwscrptutl.a  libwscrrun.a    libwscsvc.a     libwsdpblb.a    libwsecedit.a   libwseclogon.a  \
  libwsecur32.a   libwsecurity.a  libwsendcmsg.a  libwsendmail.a  libwsens.a      libwsensapi.a   \
  libwsenscfg.a   libwseo.a       libwserialui.a  libwservdeps.a  libwserwvdrv.a  libwsetupapi.a  \
  libwsfc.a       libwsfc_os.a    libwsfcfiles.a  libwsfmapi.a    libwshatm.a     libwshbth.a     \
  libwshcon.a     libzoneoc.a

lib%.a:
	$(DLLTOOL) $(DLLOPTS) --def $(top_srcdir)/lib/$*.def




crtlibsdir=$(crtdir)
crtlibs_LIBRARIES = libm.a libmingwex.a
libm_a_SOURCES = _libm_dummy.c

crtlibs_LIBRARIES += libkernel32.a
libkernel32_a_SOURCES = lib/kernel32.c
libkernel32_a_AR = \
        $(DLLTOOL) --as=$(AS) -k --output-lib $@ --def $(top_srcdir)/lib/kernel32.def; \
        $(AR) $(ARFLAGS)

crtlibs_LIBRARIES += libshell32.a
libshell32_a_SOURCES = lib/shell32.c
libshell32_a_AR = \
        $(DLLTOOL) --as=$(AS) -k --output-lib $@ --def $(top_srcdir)/lib/shell32.def; \
        $(AR) $(ARFLAGS)

crtlibs_LIBRARIES += liblargeint.a
liblargeint_a_SOURCES = lib/largeint.c

crtlibs_LIBRARIES += libscrnsave.a
libscrnsave_a_SOURCES = lib/scrnsave.c

crtlibs_LIBRARIES += libscrnsavw.a
libscrnsavw_a_SOURCES = lib/scrnsave.c
libscrnsavw_a_CFLAGS = -DUNICODE

crtlibs_LIBRARIES += libuuid.a
libuuid_a_SOURCES = lib/uuid.c lib/mshtml-uuid.c




crtlibs_LIBRARIES += libmingw32.a
libmingw32_a_SOURCES = \
  crt0_c.c crt0_w.c dll_argv.c gccmain.c CRT_fp10.c pseudo-reloc.c pseudo-reloc-list.c pesect.c cinitexe.c \
  natstart.c gs_support.c atonexit.c dllmain.c wildcard.c merr.c dllargv.c charmax.c xtxtmode.c tlssup.c   \
  xncommod.c _newmode.c xthdloc.c mingw_helpers.c dllentry.c


crtlibs_LIBRARIES += libmoldname.a
libmoldname_a_SOURCES = \
  isascii.c iscsym.c iscsymf.c toascii.c strcasecmp.c strncasecmp.c wcscmpi.
libmoldname_a_AR = \
  $(DLLTOOL) $(DLLOPTS) -U --dllname msvcrt.dll --def $(top_srcdir)/moldname-msvcrt.def; \
  $(AR) $(ARFLAGS)
  

crtlibs_LIBRARIES += libmingwex.a
libmingwex_a_SOURCES = \
  dirent.c           ftruncate.c        getopt.c          wdirent.c        \
  \
  complex/cabs.c     complex/casinhl.c  complex/cexpl.c   complex/csin.c   \
  complex/cabsf.c    complex/casinl.c   complex/cimag.c   complex/csinf.c  \
  complex/cabsl.c    complex/catan.c    complex/cimagf.c  complex/csinh.c  \
  complex/cacos.c    complex/catanf.c   complex/cimagl.c  complex/csinhf.c \
  complex/cacosf.c   complex/catanh.c   complex/clog.c    complex/csinhl.c \
  complex/cacosh.c   complex/catanhf.c  complex/clogf.c   complex/csinl.c  \
  complex/cacoshf.c  complex/catanhl.c  complex/clogl.c   complex/csqrt.c  \
  complex/cacoshl.c  complex/catanl.c   complex/cpow.c    complex/csqrtf.c \
  complex/cacosl.c   complex/ccos.c     complex/cpowf.c   complex/csqrtl.c \
  complex/carg.c     complex/ccosf.c    complex/cpowl.c   complex/ctan.c   \
  complex/cargf.c    complex/ccosh.c    complex/cproj.c   complex/ctanf.c  \
  complex/cargl.c    complex/ccoshf.c   complex/cprojf.c  complex/ctanh.c  \
  complex/casin.c    complex/ccoshl.c   complex/cprojl.c  complex/ctanhf.c \
  complex/casinf.c   complex/ccosl.c    complex/creal.c   complex/ctanhl.c \
  complex/casinh.c   complex/cexp.c     complex/crealf.c  complex/ctanl.c  \
  complex/casinhf.c  complex/cexpf.c    complex/creall.c  \
  \
  math/acosf.c         math/expm1l.c       math/ldexpl.c       math/powif.c      \
  math/acosh.c         math/fabs.c         math/lgamma.c       math/powil.c      \
  math/acoshf.c        math/fabsf.c        math/lgammaf.c      math/powl.c       \
  math/acoshl.c        math/fabsl.c        math/lgammal.c      math/remainderf.S \
  math/acosl.c         math/fastmath.h     math/llrint.c       math/remainderl.S \
  math/asinf.c         math/fdim.c         math/llrintf.c      math/remainder.S  \
  math/asinh.c         math/fdimf.c        math/llrintl.c      math/remquof.S    \
  math/asinhf.c        math/fdiml.c        math/llround.c      math/remquol.S    \
  math/asinhl.c        math/floorf.c       math/llroundf.c     math/remquo.S     \
  math/asinl.c         math/floorl.S       math/llroundl.c     math/rint.c       \
  math/atan2f.c        math/fmaf.S         math/log10f.c       math/rintf.c      \
  math/atan2l.c        math/fmal.c         math/log10l.S       math/rintl.c      \
  math/atanf.c         math/fma.S          math/log1pf.S       math/round.c      \
  math/atanh.c         math/fmax.c         math/log1pl.S       math/roundf.c     \
  math/atanhf.c        math/fmaxf.c        math/log1p.S        math/roundl.c     \
  math/atanhl.c        math/fmaxl.c        math/log2f.S        math/scalbnf.S    \
  math/atanl.c         math/fmin.c         math/log2l.S        math/scalbnl.S    \
  math/cbrt.c          math/fminf.c        math/log2.S         math/scalbn.S     \
  math/cbrtf.c         math/fminl.c        math/logb.c         math/s_erf.c      \
  math/cbrtl.c         math/fmodf.c        math/logbf.c        math/sf_erf.c     \
  math/ceilf.c         math/fmodl.c        math/logbl.c        math/signbit.c    \
  math/ceill.S         math/fpclassify.c   math/logf.c         math/signbitf.c   \
  math/cephes_emath.c  math/fpclassifyf.c  math/logl.S         math/signbitl.c   \
  math/cephes_emath.h  math/fpclassifyl.c  math/lrint.c        math/sinf.c       \
  math/cephes_mconf.h  math/fp_consts.c    math/lrintf.c       math/sinhf.c      \
  math/copysign.c      math/fp_constsf.c   math/lrintl.c       math/sinhl.c      \
  math/copysignf.c     math/fp_consts.h    math/lround.c       math/sinl.S       \
  math/copysignl.S     math/fp_constsl.c   math/lroundf.c      math/sqrtf.c      \
  math/cosf.c          math/frexpf.c       math/lroundl.c      math/sqrtl.c      \
  math/coshf.c         math/frexpl.S       math/modff.c        math/tanf.c       \
  math/coshl.c         math/fucom.c        math/modfl.c        math/tanhf.c      \
  math/cosl.S          math/hypotf.c       math/nearbyintf.S   math/tanhl.c      \
  math/erfl.c          math/hypotl.c       math/nearbyintl.S   math/tanl.S       \
  math/exp2f.S         math/ilogbf.S       math/nearbyint.S    math/tgamma.c     \
  math/exp2l.S         math/ilogbl.S       math/nextafterf.c   math/tgammaf.c    \
  math/exp2.S          math/ilogb.S        math/nextafterl.c   math/tgammal.c    \
  math/expf.c          math/isnan.c        math/nexttoward.c   math/trunc.c      \
  math/expl.c          math/isnanf.c       math/nexttowardf.c  math/truncf.c     \
  math/expm1.c         math/isnanl.c       math/powf.c         math/truncl.c     \
  math/expm1f.c        math/ldexpf.c       math/powi.c         \
  \
  misc/alarm.c            misc/fesetenv.c         misc/mb_wc_common.h          misc/wcrtomb.c        \
  misc/btowc.c            misc/fesetexceptflag.c  misc/mingw-aligned-malloc.c  misc/wcstoimax.c      \
  misc/ctime.c            misc/fesetround.c       misc/mingw-fseek.c           misc/wcstold.c        \
  misc/difftime32.c       misc/fetestexcept.c     misc/_mkgmtime.c             misc/wcstoumax.c      \
  misc/difftime64.c       misc/feupdateenv.c      misc/mktime.c                misc/wctob.c          \
  misc/difftime.c         misc/fwide.c            misc/seterrno.c              misc/wctrans.c        \
  misc/execv.c            misc/getlogin.c         misc/sleep.c                 misc/wctype.c         \
  misc/execve.c           misc/gettimeofday.c     misc/spawnv.c                misc/wininterlocked.c \
  misc/execvp.c           misc/gmtime.c           misc/spawnve.c               misc/wmemchr.c        \
  misc/execvpe.c          misc/imaxabs.c          misc/spawnvp.c               misc/wmemcmp.c        \
  misc/feclearexcept.c    misc/imaxdiv.c          misc/spawnvpe.c              misc/wmemcpy.c        \
  misc/fegetenv.c         misc/isblank.c          misc/strtoimax.c             misc/wmemmove.c       \
  misc/fegetexceptflag.c  misc/iswblank.c         misc/strtold.c               misc/wmemset.c        \
  misc/fegetround.c       misc/localtime.c        misc/strtoumax.c \
  misc/feholdexcept.c     misc/mbrtowc.c          misc/time.c      \
  misc/feraiseexcept.c    misc/mbsinit.c          misc/wassert.c   \
  \
  stdio/atoll.c            stdio/ftello64.c      stdio/strtof.c     stdio/vsnwprintf.c \
  stdio/_Exit.c            stdio/_fwstat64i32.c  stdio/ulltoa.c     stdio/vsscanf.c    \
  stdio/_findfirst64i32.c  stdio/lltoa.c         stdio/ulltow.c     stdio/vswscanf.c   \
  stdio/_findnext64i32.c   stdio/lltow.c         stdio/vfscanf.c    stdio/vwscanf.c    \
  stdio/fopen64.c          stdio/lseek64.c       stdio/vfwscanf.c   stdio/wcstof.c     \
  stdio/fseeko64.c         stdio/snprintf.c      stdio/vscanf.c     stdio/wtoll.c      \
  stdio/_fstat64i32.c      stdio/snwprintf.c     stdio/vsnprintf.c  



CLEANFILES = $(BUILT_SOURCES) $(crt_SCRIPTS)
EXTRA_DIST = crtdll.def msvcrt.def msvcr80.def crtexe.c crtdll.c lib
noinst_HEADERS = \
  misc/mb_wc_common.h internal.h oscalls.h sect_attribs.h math/fp_consts.h \
  math/cephes_mconf.h math/fastmath.h math/cephes_emath.h

