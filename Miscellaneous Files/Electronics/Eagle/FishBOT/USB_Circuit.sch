<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.3.1">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="Micro_USB">
<description>&lt;b&gt;USB PCB CONNECTORS&lt;/b&gt;&lt;br/&gt;
from &lt;a href="http://www.molex.com/"&gt;MOLEX&lt;/a&gt;.&lt;br/&gt;
&lt;br/&gt;
(C) 2014 Tomasz Boleslaw CEDRO, cederom@tlen.pl, &lt;a href="http://www.tomek.cedro.info"&gt;http://www.tomek.cedro.info&lt;/a&gt;.&lt;br/&gt;
&lt;br/&gt;
Version 0.1 (2014-01-17): Initial release.</description>
<packages>
<package name="47589-0001">
<description>&lt;b&gt;MICRO USB RECEPTACLES&lt;/b&gt;&lt;br/&gt;
&lt;i&gt;Micro-USB Receptacles, SMT, Lead-Free&lt;/i&gt;&lt;br/&gt;
from &lt;a href="http://www.molex.com/"&gt;MOLEX&lt;/a&gt;.&lt;br/&gt;
&lt;br/&gt;
(C) 2014 Tomasz Boleslaw CEDRO, cederom@tlen.pl, &lt;a href="http://www.tomek.cedro.info"&gt;http://www.tomek.cedro.info&lt;/a&gt;.&lt;br/&gt;
&lt;br/&gt;
Version 0.1 (2014-01-17): Initial release.&lt;br/&gt;
Version 0.2 (2014-02-06): Updated 47589-0001 footprint pins/pads/milling.&lt;br/&gt;
&lt;br/&gt;
Following devices are included:&lt;br/&gt;
1. &lt;a href="http://www.molex.com/molex/products/datasheet.jsp?part=active/0475890001_IO_CONNECTORS.xml"&gt;47589-0001

Micro-USB AB Receptacle, Bottom Mount, SMT, Lead-Free&lt;/a&gt; (&lt;a href="http://www.molex.com/pdm_docs/sd/475890001_sd.pdf"&gt;Technical Drawing&lt;/a&gt;).
&lt;br/&gt;</description>
<wire x1="-1.45" y1="4" x2="-1.45" y2="-4" width="0.05" layer="51" style="shortdash"/>
<wire x1="-2.15" y1="3.75" x2="2.85" y2="3.75" width="0.05" layer="21"/>
<wire x1="2.85" y1="3.75" x2="2.85" y2="-3.75" width="0.05" layer="21"/>
<wire x1="2.85" y1="-3.75" x2="-2.15" y2="-3.75" width="0.05" layer="21"/>
<wire x1="-2.15" y1="-3.75" x2="-2.15" y2="3.75" width="0.05" layer="21"/>
<wire x1="2.85" y1="3.75" x2="2.85" y2="2.5" width="0.05" layer="51"/>
<wire x1="2.85" y1="2.5" x2="2.85" y2="1.95" width="0.05" layer="51"/>
<wire x1="2.85" y1="1.95" x2="2.85" y2="-1.95" width="0.05" layer="51"/>
<wire x1="2.85" y1="-1.95" x2="2.85" y2="-2.5" width="0.05" layer="51"/>
<wire x1="2.85" y1="-2.5" x2="2.85" y2="-3.75" width="0.05" layer="51"/>
<wire x1="2.85" y1="-3.75" x2="-2.15" y2="-3.75" width="0.05" layer="51"/>
<wire x1="-2.15" y1="-3.75" x2="-2.15" y2="-3.2" width="0.05" layer="51"/>
<wire x1="-2.15" y1="-3.2" x2="-2.15" y2="3.2" width="0.05" layer="51"/>
<wire x1="-2.15" y1="3.2" x2="-2.15" y2="3.75" width="0.05" layer="51"/>
<wire x1="-2.15" y1="3.75" x2="2.85" y2="3.75" width="0.05" layer="51"/>
<wire x1="2.85" y1="2.5" x2="3.05" y2="2.5" width="0.05" layer="51"/>
<wire x1="3.05" y1="2.5" x2="3.05" y2="1.95" width="0.05" layer="51"/>
<wire x1="3.05" y1="1.95" x2="2.85" y2="1.95" width="0.05" layer="51"/>
<wire x1="2.85" y1="-1.95" x2="3.05" y2="-1.95" width="0.05" layer="51"/>
<wire x1="3.05" y1="-1.95" x2="3.05" y2="-2.5" width="0.05" layer="51"/>
<wire x1="3.05" y1="-2.5" x2="2.85" y2="-2.5" width="0.05" layer="51"/>
<wire x1="-2.15" y1="-3.75" x2="-2.75" y2="-4.1" width="0.05" layer="51"/>
<wire x1="-2.15" y1="3.75" x2="-2.75" y2="4.1" width="0.05" layer="51"/>
<wire x1="-2.75" y1="3.2" x2="-2.75" y2="-3.2" width="0.05" layer="51"/>
<wire x1="-2.75" y1="-3.2" x2="-2.15" y2="-3.2" width="0.05" layer="51"/>
<wire x1="-2.75" y1="3.2" x2="-2.15" y2="3.2" width="0.05" layer="51"/>
<wire x1="-0.65" y1="3.875" x2="-0.65" y2="4.475" width="0" layer="46"/>
<wire x1="-0.65" y1="4.475" x2="0.65" y2="4.475" width="0" layer="46"/>
<wire x1="0.65" y1="4.475" x2="0.65" y2="3.875" width="0" layer="46"/>
<wire x1="0.65" y1="3.875" x2="-0.65" y2="3.875" width="0" layer="46"/>
<wire x1="0.65" y1="-3.875" x2="-0.65" y2="-3.875" width="0" layer="46"/>
<wire x1="-0.65" y1="-3.875" x2="-0.65" y2="-4.475" width="0" layer="46"/>
<wire x1="-0.65" y1="-4.475" x2="0.65" y2="-4.475" width="0" layer="46"/>
<wire x1="0.65" y1="-4.475" x2="0.65" y2="-3.875" width="0" layer="46"/>
<wire x1="2.575" y1="1.875" x2="3.425" y2="1.875" width="0" layer="46"/>
<wire x1="3.425" y1="1.875" x2="3.425" y2="2.575" width="0" layer="46"/>
<wire x1="3.425" y1="2.575" x2="2.575" y2="2.575" width="0" layer="46"/>
<wire x1="2.575" y1="2.575" x2="2.575" y2="1.875" width="0" layer="46"/>
<wire x1="3.425" y1="-1.875" x2="3.425" y2="-2.575" width="0" layer="46"/>
<wire x1="3.425" y1="-2.575" x2="2.575" y2="-2.575" width="0" layer="46"/>
<wire x1="2.575" y1="-2.575" x2="2.575" y2="-1.875" width="0" layer="46"/>
<wire x1="2.575" y1="-1.875" x2="3.425" y2="-1.875" width="0" layer="46"/>
<pad name="CASING2" x="0" y="-4.175" drill="0.6" diameter="0.95" shape="long" thermals="no"/>
<pad name="CASING1" x="0" y="4.175" drill="0.6" diameter="0.95" shape="long" thermals="no"/>
<pad name="CASING3" x="3" y="2.225" drill="0.7" diameter="1.1" shape="long"/>
<pad name="CASING4" x="3" y="-2.225" drill="0.7" diameter="1.1" shape="long"/>
<smd name="5" x="2.8" y="-1.3" dx="1.35" dy="0.4" layer="1"/>
<smd name="4" x="2.8" y="-0.65" dx="1.35" dy="0.4" layer="1"/>
<smd name="3" x="2.8" y="0" dx="1.35" dy="0.4" layer="1"/>
<smd name="2" x="2.8" y="0.65" dx="1.35" dy="0.4" layer="1"/>
<smd name="1" x="2.8" y="1.3" dx="1.35" dy="0.4" layer="1"/>
<rectangle x1="-0.95" y1="0.25" x2="0.95" y2="2.05" layer="1"/>
<rectangle x1="-0.95" y1="2.6" x2="0.95" y2="4.175" layer="1"/>
<rectangle x1="-0.95" y1="-2.05" x2="0.95" y2="-0.25" layer="1" rot="R180"/>
<rectangle x1="-0.95" y1="-4.175" x2="0.95" y2="-2.6" layer="1" rot="R180"/>
<rectangle x1="-0.95" y1="-2.05" x2="0.95" y2="-0.25" layer="29" rot="R180"/>
<rectangle x1="-0.95" y1="-4.175" x2="0.95" y2="-2.6" layer="29" rot="R180"/>
<rectangle x1="-0.95" y1="0.25" x2="0.95" y2="2.05" layer="29"/>
<rectangle x1="-0.95" y1="2.6" x2="0.95" y2="4.175" layer="29"/>
</package>
</packages>
<symbols>
<symbol name="MICRO-USB-AB-RECEPTACLE">
<wire x1="-2.54" y1="6.35" x2="-2.54" y2="-6.35" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-6.35" x2="-1.27" y2="-7.62" width="0.254" layer="94" curve="90"/>
<wire x1="-1.27" y1="-7.62" x2="0" y2="-7.62" width="0.254" layer="94"/>
<wire x1="0" y1="-7.62" x2="1.016" y2="-8.128" width="0.254" layer="94" curve="-53.130102"/>
<wire x1="1.016" y1="-8.128" x2="2.54" y2="-8.89" width="0.254" layer="94" curve="53.130102"/>
<wire x1="2.54" y1="-8.89" x2="5.08" y2="-8.89" width="0.254" layer="94"/>
<wire x1="5.08" y1="-8.89" x2="6.35" y2="-7.62" width="0.254" layer="94" curve="90"/>
<wire x1="6.35" y1="-7.62" x2="6.35" y2="7.62" width="0.254" layer="94"/>
<wire x1="-2.54" y1="6.35" x2="-1.27" y2="7.62" width="0.254" layer="94" curve="-90"/>
<wire x1="-1.27" y1="7.62" x2="0" y2="7.62" width="0.254" layer="94"/>
<wire x1="0" y1="7.62" x2="1.016" y2="8.128" width="0.254" layer="94" curve="53.130102"/>
<wire x1="1.016" y1="8.128" x2="2.54" y2="8.89" width="0.254" layer="94" curve="-53.130102"/>
<wire x1="2.54" y1="8.89" x2="5.08" y2="8.89" width="0.254" layer="94"/>
<wire x1="5.08" y1="8.89" x2="6.35" y2="7.62" width="0.254" layer="94" curve="-90"/>
<wire x1="0" y1="5.08" x2="0" y2="-5.08" width="0.254" layer="94"/>
<wire x1="0" y1="-5.08" x2="1.27" y2="-6.35" width="0.254" layer="94"/>
<wire x1="1.27" y1="-6.35" x2="3.81" y2="-6.35" width="0.254" layer="94"/>
<wire x1="3.81" y1="-6.35" x2="3.81" y2="6.35" width="0.254" layer="94"/>
<wire x1="3.81" y1="6.35" x2="1.27" y2="6.35" width="0.254" layer="94"/>
<wire x1="1.27" y1="6.35" x2="0" y2="5.08" width="0.254" layer="94"/>
<wire x1="-2.54" y1="10.16" x2="7.62" y2="10.16" width="0.254" layer="94" style="shortdash"/>
<wire x1="7.62" y1="10.16" x2="7.62" y2="-10.16" width="0.254" layer="94" style="shortdash"/>
<wire x1="7.62" y1="-10.16" x2="-2.54" y2="-10.16" width="0.254" layer="94" style="shortdash"/>
<text x="-2.54" y="11.43" size="1.778" layer="95" font="vector">&gt;NAME</text>
<text x="10.16" y="-7.62" size="1.778" layer="96" font="vector" rot="R90">&gt;VALUE</text>
<pin name="1" x="-5.08" y="5.08" visible="pin" direction="in"/>
<pin name="2" x="-5.08" y="2.54" visible="pin" direction="in"/>
<pin name="3" x="-5.08" y="0" visible="pin" direction="in"/>
<pin name="4" x="-5.08" y="-2.54" visible="pin" direction="in"/>
<pin name="5" x="-5.08" y="-5.08" visible="pin" direction="in"/>
<pin name="GND1" x="-2.54" y="-12.7" visible="off" length="short" rot="R90"/>
<pin name="GND2" x="0" y="-12.7" visible="off" length="short" rot="R90"/>
<pin name="GND3" x="2.54" y="-12.7" visible="off" length="short" rot="R90"/>
<pin name="GND4" x="5.08" y="-12.7" visible="off" length="short" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MICRO-USB-RECEPTACLE">
<description>&lt;b&gt;MICRO USB RECEPTACLES&lt;/b&gt;&lt;br/&gt;
&lt;i&gt;Micro-USB Receptacles, SMT, Lead-Free&lt;/i&gt;&lt;br/&gt;
from &lt;a href="http://www.molex.com/"&gt;MOLEX&lt;/a&gt;.&lt;br/&gt;
&lt;br/&gt;
(C) 2014 Tomasz Boleslaw CEDRO, cederom@tlen.pl, &lt;a href="http://www.tomek.cedro.info"&gt;http://www.tomek.cedro.info&lt;/a&gt;.&lt;br/&gt;
&lt;br/&gt;
Version 0.1 (2014-01-17): Initial release.&lt;br/&gt;
Version 0.2 (2014-02-06): Updated 47589-0001 footprint pins/pads/milling.&lt;br/&gt;
&lt;br/&gt;
Following devices are included:&lt;br/&gt;
1. &lt;a href="http://www.molex.com/molex/products/datasheet.jsp?part=active/0475890001_IO_CONNECTORS.xml"&gt;47589-0001

Micro-USB AB Receptacle, Bottom Mount, SMT, Lead-Free&lt;/a&gt; (&lt;a href="http://www.molex.com/pdm_docs/sd/475890001_sd.pdf"&gt;Technical Drawing&lt;/a&gt;).
&lt;br/&gt;</description>
<gates>
<gate name="G$1" symbol="MICRO-USB-AB-RECEPTACLE" x="-2.54" y="0"/>
</gates>
<devices>
<device name="47589-0001" package="47589-0001">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="GND1" pad="CASING1"/>
<connect gate="G$1" pin="GND2" pad="CASING2"/>
<connect gate="G$1" pin="GND3" pad="CASING3"/>
<connect gate="G$1" pin="GND4" pad="CASING4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U$1" library="Micro_USB" deviceset="MICRO-USB-RECEPTACLE" device="47589-0001"/>
<part name="U$2" library="Micro_USB" deviceset="MICRO-USB-RECEPTACLE" device="47589-0001"/>
<part name="U$3" library="Micro_USB" deviceset="MICRO-USB-RECEPTACLE" device="47589-0001"/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="40.64" y="50.8" smashed="yes" rot="R180">
<attribute name="NAME" x="43.18" y="39.37" size="1.778" layer="95" font="vector" rot="R180"/>
</instance>
<instance part="U$2" gate="G$1" x="55.88" y="66.04" smashed="yes">
<attribute name="NAME" x="53.34" y="77.47" size="1.778" layer="95" font="vector"/>
</instance>
<instance part="U$3" gate="G$1" x="55.88" y="38.1" smashed="yes">
<attribute name="NAME" x="53.34" y="49.53" size="1.778" layer="95" font="vector"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="5"/>
<wire x1="45.72" y1="55.88" x2="50.8" y2="55.88" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="5"/>
<wire x1="50.8" y1="55.88" x2="50.8" y2="60.96" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="5"/>
<wire x1="50.8" y1="33.02" x2="30.48" y2="33.02" width="0.1524" layer="91"/>
<wire x1="30.48" y1="33.02" x2="30.48" y2="55.88" width="0.1524" layer="91"/>
<wire x1="30.48" y1="55.88" x2="45.72" y2="55.88" width="0.1524" layer="91"/>
<junction x="45.72" y="55.88"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="3"/>
<wire x1="45.72" y1="50.8" x2="66.04" y2="50.8" width="0.1524" layer="91"/>
<wire x1="66.04" y1="50.8" x2="66.04" y2="66.04" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="3"/>
<wire x1="66.04" y1="66.04" x2="50.8" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="2"/>
<wire x1="50.8" y1="68.58" x2="68.58" y2="68.58" width="0.1524" layer="91"/>
<wire x1="68.58" y1="68.58" x2="68.58" y2="48.26" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="2"/>
<wire x1="68.58" y1="48.26" x2="45.72" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="4"/>
<wire x1="50.8" y1="63.5" x2="48.26" y2="63.5" width="0.1524" layer="91"/>
<wire x1="48.26" y1="63.5" x2="48.26" y2="53.34" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="4"/>
<wire x1="48.26" y1="53.34" x2="45.72" y2="53.34" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="1"/>
<wire x1="50.8" y1="71.12" x2="33.02" y2="71.12" width="0.1524" layer="91"/>
<wire x1="33.02" y1="71.12" x2="33.02" y2="45.72" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="1"/>
<pinref part="U$3" gate="G$1" pin="1"/>
<wire x1="45.72" y1="45.72" x2="50.8" y2="45.72" width="0.1524" layer="91"/>
<wire x1="50.8" y1="45.72" x2="50.8" y2="43.18" width="0.1524" layer="91"/>
<wire x1="33.02" y1="45.72" x2="45.72" y2="45.72" width="0.1524" layer="91"/>
<junction x="45.72" y="45.72"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
