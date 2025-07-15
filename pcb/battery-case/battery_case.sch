<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.6.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="24" fill="1" visible="no" active="no"/>
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
<layer number="99" name="SpiceOrder" color="5" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="custom_battery_case">
<packages>
<package name="CASE">
<wire x1="-38.5" y1="20" x2="38.5" y2="20" width="0.127" layer="21"/>
<wire x1="-38.5" y1="20" x2="-38.5" y2="-20" width="0.127" layer="21"/>
<wire x1="38.5" y1="20" x2="38.5" y2="-20" width="0.127" layer="21"/>
<wire x1="-38.5" y1="-20" x2="38.5" y2="-20" width="0.127" layer="21"/>
<smd name="P$3" x="-41.75" y="9.75" dx="6.5" dy="8.5" layer="1"/>
<smd name="P$4" x="41.75" y="9.75" dx="6.5" dy="8.5" layer="1"/>
<smd name="P$1" x="-41.75" y="-9.75" dx="6.5" dy="8.5" layer="1"/>
<smd name="P$2" x="41.75" y="-9.75" dx="6.5" dy="8.5" layer="1"/>
</package>
</packages>
<symbols>
<symbol name="BATTERY">
<wire x1="-12.7" y1="5.08" x2="-10.16" y2="5.08" width="0.254" layer="94"/>
<wire x1="-10.16" y1="5.08" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="5.08" x2="-2.54" y2="5.08" width="0.254" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="-2.54" y2="-12.7" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-12.7" x2="-12.7" y2="-12.7" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-12.7" x2="-12.7" y2="5.08" width="0.254" layer="94"/>
<wire x1="-10.16" y1="5.08" x2="-10.16" y2="7.62" width="0.254" layer="94"/>
<wire x1="-10.16" y1="7.62" x2="-5.08" y2="7.62" width="0.254" layer="94"/>
<wire x1="-5.08" y1="7.62" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="2.54" y1="5.08" x2="5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="5.08" x2="10.16" y2="5.08" width="0.254" layer="94"/>
<wire x1="10.16" y1="5.08" x2="12.7" y2="5.08" width="0.254" layer="94"/>
<wire x1="12.7" y1="5.08" x2="12.7" y2="-12.7" width="0.254" layer="94"/>
<wire x1="12.7" y1="-12.7" x2="2.54" y2="-12.7" width="0.254" layer="94"/>
<wire x1="2.54" y1="-12.7" x2="2.54" y2="5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="5.08" x2="5.08" y2="7.62" width="0.254" layer="94"/>
<wire x1="5.08" y1="7.62" x2="10.16" y2="7.62" width="0.254" layer="94"/>
<wire x1="10.16" y1="7.62" x2="10.16" y2="5.08" width="0.254" layer="94"/>
<pin name="P$1" x="-7.62" y="10.16" length="short" rot="R270"/>
<pin name="P$2" x="-7.62" y="-15.24" length="short" rot="R90"/>
<pin name="P$3" x="7.62" y="10.16" length="short" rot="R270"/>
<pin name="P$4" x="7.62" y="-15.24" length="short" rot="R90"/>
<text x="-15.24" y="-7.62" size="1.778" layer="94" rot="R90">&gt;NAME</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="BATTERY_CASE" prefix="CASE">
<gates>
<gate name="G$1" symbol="BATTERY" x="0" y="2.54"/>
</gates>
<devices>
<device name="" package="CASE">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
<connect gate="G$1" pin="P$3" pad="P$3"/>
<connect gate="G$1" pin="P$4" pad="P$4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-phoenix-508" urn="urn:adsk.eagle:library:176">
<description>&lt;b&gt;Phoenix Connectors&lt;/b&gt;&lt;p&gt;
Grid 5.08 mm&lt;p&gt;
Based on the previous libraries:
&lt;ul&gt;
&lt;li&gt;pho508a.lbr
&lt;li&gt;pho508b.lbr
&lt;li&gt;pho508c.lbr
&lt;li&gt;pho508d.lbr
&lt;li&gt;pho508e.lbr
&lt;/ul&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="MKDSN1,5/2-5,08" urn="urn:adsk.eagle:footprint:9541/1" library_version="3">
<description>&lt;b&gt;MKDSN 1,5/ 2-5,08&lt;/b&gt; Printklemme&lt;p&gt;
Nennstrom: 13,5 A&lt;br&gt;
Nennspannung: 250 V&lt;br&gt;
Rastermaß: 5,08 mm&lt;br&gt;
Polzahl: 2&lt;br&gt;
Anschlussart: Schraubanschluss&lt;br&gt;
Montage: Löten&lt;br&gt;
Anschlussrichtung Leiter/Platine: 0 °&lt;br&gt;
Artikelnummer: 1729128&lt;br&gt;
Source: http://eshop.phoenixcontact.com .. 1729128.pdf</description>
<wire x1="-5.1011" y1="-4.05" x2="5.0589" y2="-4.05" width="0.2032" layer="21"/>
<wire x1="-5.1011" y1="2.5243" x2="5.0589" y2="2.5243" width="0.2032" layer="21"/>
<wire x1="-2.7211" y1="-0.63" x2="-3.6341" y2="-1.543" width="0.2032" layer="51"/>
<wire x1="-5.1011" y1="-1.9555" x2="-5.1011" y2="-2.4479" width="0.2032" layer="21"/>
<wire x1="-5.1011" y1="-3.327" x2="-5.2298" y2="-3.327" width="0.2032" layer="21"/>
<wire x1="-5.2298" y1="-2.913" x2="-5.1011" y2="-2.913" width="0.2032" layer="21"/>
<wire x1="-5.1011" y1="-3.1279" x2="-5.1011" y2="-2.913" width="0.2032" layer="21"/>
<wire x1="-5.1011" y1="-3.327" x2="-5.1011" y2="-3.1279" width="0.2032" layer="21"/>
<wire x1="-5.6711" y1="-2.763" x2="-5.4081" y2="-2.763" width="0.2032" layer="21"/>
<wire x1="-5.6711" y1="-3.477" x2="-5.4081" y2="-3.477" width="0.2032" layer="21"/>
<wire x1="-5.1011" y1="-2.913" x2="-5.1011" y2="-2.4479" width="0.2032" layer="21"/>
<wire x1="-5.2298" y1="-3.327" x2="-5.4081" y2="-3.477" width="0.2032" layer="21"/>
<wire x1="-5.6711" y1="-2.763" x2="-5.6711" y2="-3.477" width="0.2032" layer="21"/>
<wire x1="-5.1011" y1="2.5243" x2="-5.1011" y2="2.0413" width="0.2032" layer="21"/>
<wire x1="-5.1011" y1="-1.9555" x2="-5.1011" y2="2.0413" width="0.2032" layer="21"/>
<wire x1="-5.4081" y1="-2.763" x2="-5.2298" y2="-2.913" width="0.2032" layer="21"/>
<wire x1="5.0589" y1="-2.4479" x2="-5.1011" y2="-2.4479" width="0.2032" layer="21"/>
<wire x1="-2.5611" y1="-0.47" x2="-2.7211" y2="-0.63" width="0.2032" layer="51"/>
<wire x1="-3.2001" y1="-0.119" x2="-2.5611" y2="0.52" width="0.2032" layer="51"/>
<wire x1="-4.1291" y1="-1.048" x2="-3.2001" y2="-0.119" width="0.2032" layer="51"/>
<wire x1="0.9509" y1="-1.048" x2="1.8799" y2="-0.119" width="0.2032" layer="51"/>
<wire x1="5.0589" y1="-1.9555" x2="5.0589" y2="-2.4479" width="0.2032" layer="21"/>
<wire x1="2.3589" y1="-0.63" x2="1.4459" y2="-1.543" width="0.2032" layer="51"/>
<wire x1="1.8799" y1="-0.119" x2="2.5189" y2="0.52" width="0.2032" layer="51"/>
<wire x1="2.5189" y1="-0.47" x2="2.3589" y2="-0.63" width="0.2032" layer="51"/>
<wire x1="4.0869" y1="1.098" x2="3.1489" y2="0.16" width="0.2032" layer="51"/>
<wire x1="2.6379" y1="0.639" x2="3.5919" y2="1.593" width="0.2032" layer="51"/>
<wire x1="3.1489" y1="0.16" x2="2.5189" y2="-0.47" width="0.2032" layer="51"/>
<wire x1="2.5189" y1="0.52" x2="2.6379" y2="0.639" width="0.2032" layer="51"/>
<wire x1="-1.9311" y1="0.16" x2="-2.5611" y2="-0.47" width="0.2032" layer="51"/>
<wire x1="-2.5611" y1="0.52" x2="-2.4421" y2="0.639" width="0.2032" layer="51"/>
<wire x1="-2.4421" y1="0.639" x2="-1.4881" y2="1.593" width="0.2032" layer="51"/>
<wire x1="-0.9931" y1="1.098" x2="-1.9311" y2="0.16" width="0.2032" layer="51"/>
<wire x1="-5.1011" y1="-3.1279" x2="5.0589" y2="-3.1279" width="0.2032" layer="21"/>
<wire x1="5.0589" y1="-3.1279" x2="5.0589" y2="-2.4479" width="0.2032" layer="21"/>
<wire x1="5.0589" y1="-1.9555" x2="5.0589" y2="2.0413" width="0.2032" layer="21"/>
<wire x1="5.0589" y1="2.5243" x2="5.0589" y2="2.0413" width="0.2032" layer="21"/>
<wire x1="5.0589" y1="2.5243" x2="5.0589" y2="4.05" width="0.2032" layer="21"/>
<wire x1="-5.1011" y1="-3.75" x2="-5.1011" y2="-3.327" width="0.2032" layer="21"/>
<wire x1="5.0589" y1="-3.75" x2="5.0589" y2="-3.1279" width="0.2032" layer="21"/>
<wire x1="-5.1011" y1="4.05" x2="5.0589" y2="4.05" width="0.2032" layer="21"/>
<wire x1="-5.1011" y1="2.5243" x2="-5.1011" y2="4.05" width="0.2032" layer="21"/>
<wire x1="5.0589" y1="-3.75" x2="-5.1011" y2="-3.75" width="0.2032" layer="21"/>
<wire x1="-5.1011" y1="-3.75" x2="-5.1011" y2="-4.05" width="0.2032" layer="21"/>
<wire x1="5.0589" y1="-3.75" x2="5.0589" y2="-4.05" width="0.2032" layer="21"/>
<wire x1="-3.2001" y1="-0.119" x2="-2.7211" y2="-0.63" width="0.2032" layer="51" curve="65.201851"/>
<wire x1="1.8799" y1="-0.119" x2="2.3589" y2="-0.63" width="0.2032" layer="51" curve="65.201851"/>
<wire x1="3.1489" y1="0.16" x2="2.6379" y2="0.639" width="0.2032" layer="51" curve="65.201851"/>
<wire x1="-1.9311" y1="0.16" x2="-2.4421" y2="0.639" width="0.2032" layer="51" curve="65.201851"/>
<circle x="-2.5611" y="0.025" radius="1.915" width="0.2032" layer="21"/>
<circle x="2.5189" y="0.025" radius="1.915" width="0.2032" layer="21"/>
<pad name="1" x="-2.5611" y="0.025" drill="1.3" diameter="2"/>
<pad name="2" x="2.5189" y="0.025" drill="1.3" diameter="2"/>
<text x="-4.7511" y="4.445" size="1.27" layer="25">&gt;NAME</text>
<text x="6.985" y="-3.81" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
</package>
</packages>
<packages3d>
<package3d name="MKDSN1,5/2-5,08" urn="urn:adsk.eagle:package:9630/1" type="box" library_version="3">
<description>MKDSN 1,5/ 2-5,08 Printklemme
Nennstrom: 13,5 A
Nennspannung: 250 V
Rastermaß: 5,08 mm
Polzahl: 2
Anschlussart: Schraubanschluss
Montage: Löten
Anschlussrichtung Leiter/Platine: 0 °
Artikelnummer: 1729128
Source: http://eshop.phoenixcontact.com .. 1729128.pdf</description>
<packageinstances>
<packageinstance name="MKDSN1,5/2-5,08"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="KLV" urn="urn:adsk.eagle:symbol:9467/1" library_version="3">
<circle x="1.27" y="0" radius="1.27" width="0.254" layer="94"/>
<circle x="1.27" y="0" radius="1.27" width="0.254" layer="94"/>
<circle x="1.27" y="0" radius="1.27" width="0.254" layer="94"/>
<text x="3.048" y="-0.889" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-3.683" size="1.778" layer="96">&gt;VALUE</text>
<pin name="KL" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MKDSN1,5/2-5,08" urn="urn:adsk.eagle:component:9705/2" prefix="X" library_version="3">
<description>&lt;b&gt;MKDSN 1,5/ 2-5,08&lt;/b&gt; Printklemme&lt;p&gt;
Nennstrom: 13,5 A&lt;br&gt;
Nennspannung: 250 V&lt;br&gt;
Rastermaß: 5,08 mm&lt;br&gt;
Polzahl: 2&lt;br&gt;
Anschlussart: Schraubanschluss&lt;br&gt;
Montage: Löten&lt;br&gt;
Anschlussrichtung Leiter/Platine: 0 °&lt;br&gt;
Artikelnummer: 1729128&lt;br&gt;
Source: http://eshop.phoenixcontact.com .. 1729128.pdf</description>
<gates>
<gate name="-1" symbol="KLV" x="0" y="0" addlevel="always" swaplevel="1"/>
<gate name="-2" symbol="KLV" x="0" y="-5.08" addlevel="always" swaplevel="1"/>
</gates>
<devices>
<device name="" package="MKDSN1,5/2-5,08">
<connects>
<connect gate="-1" pin="KL" pad="1"/>
<connect gate="-2" pin="KL" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:9630/1"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="POPULARITY" value="14" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="87583-2010BLF">
<description>&lt;USB 2.0, Input Output Connectors, Receptacle, Type A, Standard, Right Angle, Surface Mount, Single Deck, 4 Positions&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="875832010BLF">
<description>&lt;b&gt;87583-2010BLF-3&lt;/b&gt;&lt;br&gt;
</description>
<smd name="1" x="-3.5" y="6.86" dx="2.88" dy="1.12" layer="1" rot="R90"/>
<smd name="2" x="-1" y="6.86" dx="2.88" dy="1.12" layer="1" rot="R90"/>
<smd name="3" x="1" y="6.86" dx="2.88" dy="1.12" layer="1" rot="R90"/>
<smd name="4" x="3.5" y="6.86" dx="2.88" dy="1.12" layer="1" rot="R90"/>
<pad name="MH1" x="-6.57" y="3.28" drill="2.3" diameter="3.45"/>
<pad name="MH2" x="6.57" y="3.28" drill="2.3" diameter="3.45"/>
<text x="0" y="0.65" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="0.65" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-7.25" y1="7" x2="7.25" y2="7" width="0.1" layer="51"/>
<wire x1="7.25" y1="7" x2="7.25" y2="-7" width="0.1" layer="51"/>
<wire x1="7.25" y1="-7" x2="-7.25" y2="-7" width="0.1" layer="51"/>
<wire x1="-7.25" y1="-7" x2="-7.25" y2="7" width="0.1" layer="51"/>
<wire x1="-9.295" y1="9.3" x2="9.295" y2="9.3" width="0.1" layer="51"/>
<wire x1="9.295" y1="9.3" x2="9.295" y2="-8" width="0.1" layer="51"/>
<wire x1="9.295" y1="-8" x2="-9.295" y2="-8" width="0.1" layer="51"/>
<wire x1="-9.295" y1="-8" x2="-9.295" y2="9.3" width="0.1" layer="51"/>
<wire x1="-4.5" y1="7" x2="-7.25" y2="7" width="0.2" layer="21"/>
<wire x1="-7.25" y1="7" x2="-7.25" y2="5.5" width="0.2" layer="21"/>
<wire x1="4.5" y1="7" x2="7.25" y2="7" width="0.2" layer="21"/>
<wire x1="7.25" y1="7" x2="7.25" y2="5.5" width="0.2" layer="21"/>
<wire x1="-7.25" y1="1" x2="-7.25" y2="-7" width="0.2" layer="21"/>
<wire x1="-7.25" y1="-7" x2="7.25" y2="-7" width="0.2" layer="21"/>
<wire x1="7.25" y1="-7" x2="7.25" y2="1" width="0.2" layer="21"/>
<wire x1="-3.5" y1="8.7" x2="-3.5" y2="8.7" width="0.1" layer="21"/>
<wire x1="-3.5" y1="8.7" x2="-3.5" y2="8.8" width="0.1" layer="21" curve="180"/>
<wire x1="-3.5" y1="8.8" x2="-3.5" y2="8.8" width="0.1" layer="21"/>
<wire x1="-3.5" y1="8.8" x2="-3.5" y2="8.7" width="0.1" layer="21" curve="180"/>
</package>
</packages>
<symbols>
<symbol name="87583-2010BLF">
<wire x1="5.08" y1="2.54" x2="17.78" y2="2.54" width="0.254" layer="94"/>
<wire x1="17.78" y1="-10.16" x2="17.78" y2="2.54" width="0.254" layer="94"/>
<wire x1="17.78" y1="-10.16" x2="5.08" y2="-10.16" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-10.16" width="0.254" layer="94"/>
<text x="19.05" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="19.05" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="1" x="22.86" y="0" length="middle" rot="R180"/>
<pin name="2" x="22.86" y="-2.54" length="middle" rot="R180"/>
<pin name="3" x="22.86" y="-5.08" length="middle" rot="R180"/>
<pin name="4" x="22.86" y="-7.62" length="middle" rot="R180"/>
<pin name="MH1" x="0" y="0" length="middle"/>
<pin name="MH2" x="0" y="-2.54" length="middle"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="87583-2010BLF" prefix="J">
<description>&lt;b&gt;USB 2.0, Input Output Connectors, Receptacle, Type A, Standard, Right Angle, Surface Mount, Single Deck, 4 Positions&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://cdn.amphenol-cs.com/media/wysiwyg/files/drawing/87583.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="87583-2010BLF" x="0" y="0"/>
</gates>
<devices>
<device name="" package="875832010BLF">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="MH1" pad="MH1"/>
<connect gate="G$1" pin="MH2" pad="MH2"/>
</connects>
<technologies>
<technology name="">
<attribute name="DESCRIPTION" value="USB 2.0, Input Output Connectors, Receptacle, Type A, Standard, Right Angle, Surface Mount, Single Deck, 4 Positions" constant="no"/>
<attribute name="HEIGHT" value="7.94mm" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="Amphenol Communications Solutions" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="87583-2010BLF" constant="no"/>
<attribute name="MOUSER_PART_NUMBER" value="" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="" constant="no"/>
</technology>
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
<part name="CASE1" library="custom_battery_case" deviceset="BATTERY_CASE" device=""/>
<part name="X3" library="con-phoenix-508" library_urn="urn:adsk.eagle:library:176" deviceset="MKDSN1,5/2-5,08" device="" package3d_urn="urn:adsk.eagle:package:9630/1"/>
<part name="J1" library="87583-2010BLF" deviceset="87583-2010BLF" device=""/>
<part name="J2" library="87583-2010BLF" deviceset="87583-2010BLF" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="CASE1" gate="G$1" x="39.64" y="38.1" smashed="yes">
<attribute name="NAME" x="24.4" y="30.48" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="X3" gate="-1" x="72" y="15" smashed="yes">
<attribute name="NAME" x="75.048" y="14.111" size="1.778" layer="95"/>
<attribute name="VALUE" x="69.46" y="11.317" size="1.778" layer="96"/>
</instance>
<instance part="X3" gate="-2" x="72" y="9.92" smashed="yes">
<attribute name="NAME" x="75.048" y="9.031" size="1.778" layer="95"/>
<attribute name="VALUE" x="69.46" y="6.237" size="1.778" layer="96"/>
</instance>
<instance part="J1" gate="G$1" x="58.42" y="53.34" smashed="yes">
<attribute name="NAME" x="77.47" y="60.96" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="77.47" y="58.42" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="J2" gate="G$1" x="58.42" y="33.02" smashed="yes">
<attribute name="NAME" x="77.47" y="40.64" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="77.47" y="38.1" size="1.778" layer="96" align="center-left"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="B+" class="0">
<segment>
<pinref part="CASE1" gate="G$1" pin="P$3"/>
<wire x1="47.26" y1="48.26" x2="47.26" y2="50.4" width="0.1524" layer="91"/>
<wire x1="47.26" y1="50.4" x2="47.3" y2="50.4" width="0.1524" layer="91"/>
<label x="47.2" y="51" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="1"/>
<wire x1="81.28" y1="33.02" x2="83.82" y2="33.02" width="0.1524" layer="91"/>
<label x="86.36" y="33.02" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="3"/>
<wire x1="81.28" y1="27.94" x2="83.82" y2="27.94" width="0.1524" layer="91"/>
<label x="86.36" y="27.94" size="1.778" layer="95"/>
</segment>
</net>
<net name="B-" class="0">
<segment>
<pinref part="CASE1" gate="G$1" pin="P$4"/>
<wire x1="47.26" y1="22.86" x2="47.26" y2="21.1" width="0.1524" layer="91"/>
<wire x1="47.26" y1="21.1" x2="47.2" y2="21.1" width="0.1524" layer="91"/>
<label x="46.8" y="18.3" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="2"/>
<wire x1="81.28" y1="30.48" x2="83.82" y2="30.48" width="0.1524" layer="91"/>
<label x="86.36" y="30.48" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="4"/>
<wire x1="81.28" y1="25.4" x2="83.82" y2="25.4" width="0.1524" layer="91"/>
<label x="86.36" y="25.4" size="1.778" layer="95"/>
</segment>
</net>
<net name="A+" class="0">
<segment>
<pinref part="CASE1" gate="G$1" pin="P$1"/>
<wire x1="32.02" y1="48.26" x2="32" y2="48.26" width="0.1524" layer="91"/>
<wire x1="32" y1="48.26" x2="32" y2="50" width="0.1524" layer="91"/>
<label x="32.1" y="51" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="1"/>
<wire x1="81.28" y1="53.34" x2="83.82" y2="53.34" width="0.1524" layer="91"/>
<label x="86.36" y="53.34" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="3"/>
<wire x1="81.28" y1="48.26" x2="83.82" y2="48.26" width="0.1524" layer="91"/>
<label x="86.36" y="48.26" size="1.778" layer="95"/>
</segment>
</net>
<net name="A-" class="0">
<segment>
<pinref part="CASE1" gate="G$1" pin="P$2"/>
<wire x1="32.02" y1="22.86" x2="32.02" y2="21" width="0.1524" layer="91"/>
<wire x1="32.02" y1="21" x2="31.9" y2="21" width="0.1524" layer="91"/>
<label x="28.7" y="18.5" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="2"/>
<wire x1="81.28" y1="50.8" x2="83.82" y2="50.8" width="0.1524" layer="91"/>
<label x="86.36" y="50.8" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="4"/>
<wire x1="81.28" y1="45.72" x2="83.82" y2="45.72" width="0.1524" layer="91"/>
<label x="86.36" y="45.72" size="1.778" layer="95"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="X3" gate="-2" pin="KL"/>
<wire x1="69.46" y1="9.92" x2="69.46" y2="10" width="0.1524" layer="91"/>
<wire x1="69.46" y1="10" x2="67" y2="10" width="0.1524" layer="91"/>
<wire x1="67" y1="10" x2="67" y2="15" width="0.1524" layer="91"/>
<pinref part="X3" gate="-1" pin="KL"/>
<wire x1="67" y1="15" x2="69.46" y2="15" width="0.1524" layer="91"/>
<label x="61" y="10" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="MH1"/>
<pinref part="J1" gate="G$1" pin="MH2"/>
<wire x1="58.42" y1="53.34" x2="58.42" y2="50.8" width="0.1524" layer="91"/>
<pinref part="J2" gate="G$1" pin="MH1"/>
<wire x1="58.42" y1="50.8" x2="58.42" y2="33.02" width="0.1524" layer="91"/>
<junction x="58.42" y="50.8"/>
<pinref part="J2" gate="G$1" pin="MH2"/>
<wire x1="58.42" y1="30.48" x2="58.42" y2="33.02" width="0.1524" layer="91"/>
<junction x="58.42" y="33.02"/>
<label x="60.96" y="40.64" size="1.778" layer="95"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports the association of 3D packages
with devices in libraries, schematics, and board files. Those 3D
packages will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
