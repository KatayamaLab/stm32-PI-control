<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.6.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="mil" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
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
</parts>
<sheets>
<sheet>
<plain>
<text x="-1.3208" y="-0.635" size="1.27" layer="91" ratio="6" rot="SR0">*</text>
<text x="-15.2146" y="-8.6868" size="1.27" layer="91" ratio="6" rot="SR0">Default Padstyle: RX18Y33D0T</text>
<text x="-14.8082" y="-10.5664" size="1.27" layer="91" ratio="6" rot="SR0">Alt 1 Padstyle: OX60Y90D30P</text>
<text x="-14.8082" y="-12.4968" size="1.27" layer="91" ratio="6" rot="SR0">Alt 2 Padstyle: OX90Y60D30P</text>
<text x="-4.0386" y="4.7244" size="0.635" layer="91" ratio="4" rot="SR0">0.106in/2.692mm</text>
<text x="-4.9784" y="2.1844" size="0.635" layer="91" ratio="4" rot="SR0">0.01in/0.254mm</text>
<text x="4.3942" y="-0.3048" size="0.635" layer="91" ratio="4" rot="SR0">0.033in/0.838mm</text>
<text x="6.604" y="-0.3048" size="0.635" layer="91" ratio="4" rot="SR0">0.055in/1.397mm</text>
<text x="-4.0386" y="-4.3688" size="0.635" layer="91" ratio="4" rot="SR0">0.079in/2.007mm</text>
<text x="-2.5146" y="-0.635" size="1.27" layer="91" ratio="6" rot="SR0">*</text>
<text x="-1.7272" y="-0.635" size="1.27" layer="91" ratio="6" rot="SR0">&gt;Value</text>
<polygon width="0.0254" layer="91">
<vertex x="-1.0414" y="0.6477"/>
<vertex x="1.0414" y="0.6477"/>
<vertex x="1.0414" y="-0.6477"/>
<vertex x="-1.0414" y="-0.6477"/>
</polygon>
</plain>
<instances>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<wire x1="-1.016" y1="-0.4064" x2="-1.016" y2="-0.3556" width="0.1524" layer="91"/>
<wire x1="-1.016" y1="-0.3556" x2="-1.016" y2="0.3556" width="0.1524" layer="91"/>
<wire x1="-1.016" y1="0.3556" x2="-1.016" y2="0.4064" width="0.1524" layer="91"/>
<wire x1="-1.016" y1="0.4064" x2="-1.3462" y2="0.4064" width="0.1524" layer="91"/>
<wire x1="-1.3462" y1="-0.4064" x2="-1.016" y2="-0.4064" width="0.1524" layer="91"/>
<wire x1="-1.016" y1="0.3556" x2="-0.6604" y2="0.7112" width="0.1524" layer="91"/>
<wire x1="-1.016" y1="-0.3556" x2="-0.6604" y2="-0.7112" width="0.1524" layer="91"/>
<wire x1="-1.3462" y1="0.4064" x2="-1.3462" y2="1.6764" width="0.1524" layer="91"/>
<wire x1="-1.3462" y1="1.6764" x2="-1.3462" y2="4.2164" width="0.1524" layer="91"/>
<wire x1="-1.3462" y1="4.2164" x2="-1.3462" y2="4.6228" width="0.1524" layer="91"/>
<wire x1="-1.3462" y1="4.2164" x2="-2.6162" y2="4.2164" width="0.1524" layer="91"/>
<wire x1="-1.3462" y1="4.2164" x2="-1.6002" y2="4.3688" width="0.1524" layer="91"/>
<wire x1="-1.3462" y1="4.2164" x2="-1.6002" y2="4.1148" width="0.1524" layer="91"/>
<wire x1="-1.6002" y1="4.3688" x2="-1.6002" y2="4.1148" width="0.1524" layer="91"/>
<wire x1="-1.3462" y1="-0.4064" x2="-1.3462" y2="0.4064" width="0.1524" layer="91"/>
<wire x1="-1.3462" y1="1.6764" x2="-2.6162" y2="1.6764" width="0.1524" layer="91"/>
<wire x1="-1.3462" y1="1.6764" x2="-1.6002" y2="1.8288" width="0.1524" layer="91"/>
<wire x1="-1.3462" y1="1.6764" x2="-1.6002" y2="1.5748" width="0.1524" layer="91"/>
<wire x1="-1.6002" y1="1.8288" x2="-1.6002" y2="1.5748" width="0.1524" layer="91"/>
<wire x1="-1.016" y1="-0.4064" x2="-1.016" y2="-3.2512" width="0.1524" layer="91"/>
<wire x1="-1.016" y1="-3.2512" x2="-1.016" y2="-3.6068" width="0.1524" layer="91"/>
<wire x1="-1.016" y1="-3.2512" x2="-2.286" y2="-3.2512" width="0.1524" layer="91"/>
<wire x1="-1.016" y1="-3.2512" x2="-1.27" y2="-3.0988" width="0.1524" layer="91"/>
<wire x1="-1.016" y1="-3.2512" x2="-1.27" y2="-3.3528" width="0.1524" layer="91"/>
<wire x1="-1.27" y1="-3.0988" x2="-1.27" y2="-3.3528" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<wire x1="1.016" y1="0.4318" x2="1.016" y2="-0.4064" width="0.1524" layer="91"/>
<wire x1="1.016" y1="-0.4064" x2="1.3462" y2="-0.4064" width="0.1524" layer="91"/>
<wire x1="1.3462" y1="-0.4064" x2="1.3462" y2="0.4064" width="0.1524" layer="91"/>
<wire x1="1.3462" y1="0.4064" x2="1.3462" y2="0.4318" width="0.1524" layer="91"/>
<wire x1="1.3462" y1="0.4318" x2="1.016" y2="0.4318" width="0.1524" layer="91"/>
<wire x1="1.3462" y1="0.4318" x2="1.3462" y2="4.2164" width="0.1524" layer="91"/>
<wire x1="1.3462" y1="4.2164" x2="1.3462" y2="4.6228" width="0.1524" layer="91"/>
<wire x1="1.3462" y1="4.2164" x2="2.6162" y2="4.2164" width="0.1524" layer="91"/>
<wire x1="1.3462" y1="4.2164" x2="1.6002" y2="4.3688" width="0.1524" layer="91"/>
<wire x1="1.3462" y1="4.2164" x2="1.6002" y2="4.1148" width="0.1524" layer="91"/>
<wire x1="1.6002" y1="4.3688" x2="1.6002" y2="4.1148" width="0.1524" layer="91"/>
<wire x1="1.3462" y1="0.4064" x2="3.8862" y2="0.4064" width="0.1524" layer="91"/>
<wire x1="3.8862" y1="0.4064" x2="4.2672" y2="0.4064" width="0.1524" layer="91"/>
<wire x1="1.3462" y1="-0.4064" x2="3.8862" y2="-0.4064" width="0.1524" layer="91"/>
<wire x1="3.8862" y1="-0.4064" x2="4.2672" y2="-0.4064" width="0.1524" layer="91"/>
<wire x1="3.8862" y1="0.4064" x2="3.8862" y2="1.6764" width="0.1524" layer="91"/>
<wire x1="3.8862" y1="-0.4064" x2="3.8862" y2="-1.6764" width="0.1524" layer="91"/>
<wire x1="3.8862" y1="0.4064" x2="3.7592" y2="0.6604" width="0.1524" layer="91"/>
<wire x1="3.8862" y1="0.4064" x2="4.0132" y2="0.6604" width="0.1524" layer="91"/>
<wire x1="3.7592" y1="0.6604" x2="4.0132" y2="0.6604" width="0.1524" layer="91"/>
<wire x1="3.8862" y1="-0.4064" x2="3.7592" y2="-0.6604" width="0.1524" layer="91"/>
<wire x1="3.8862" y1="-0.4064" x2="4.0132" y2="-0.6604" width="0.1524" layer="91"/>
<wire x1="3.7592" y1="-0.6604" x2="4.0132" y2="-0.6604" width="0.1524" layer="91"/>
<wire x1="1.016" y1="-0.4064" x2="1.016" y2="-3.2512" width="0.1524" layer="91"/>
<wire x1="1.016" y1="-3.2512" x2="1.016" y2="-3.6068" width="0.1524" layer="91"/>
<wire x1="1.016" y1="-3.2512" x2="2.286" y2="-3.2512" width="0.1524" layer="91"/>
<wire x1="1.016" y1="-3.2512" x2="1.27" y2="-3.0988" width="0.1524" layer="91"/>
<wire x1="1.016" y1="-3.2512" x2="1.27" y2="-3.3528" width="0.1524" layer="91"/>
<wire x1="1.27" y1="-3.0988" x2="1.27" y2="-3.3528" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<wire x1="-1.016" y1="-0.7112" x2="1.016" y2="-0.7112" width="0.1524" layer="91"/>
<wire x1="1.016" y1="-0.7112" x2="1.016" y2="0.7112" width="0.1524" layer="91"/>
<wire x1="1.016" y1="0.7112" x2="-1.016" y2="0.7112" width="0.1524" layer="91"/>
<wire x1="-1.016" y1="0.7112" x2="-1.016" y2="-0.7112" width="0.1524" layer="91"/>
<wire x1="1.016" y1="0.7112" x2="6.096" y2="0.7112" width="0.1524" layer="91"/>
<wire x1="6.096" y1="0.7112" x2="6.4516" y2="0.7112" width="0.1524" layer="91"/>
<wire x1="1.016" y1="-0.7112" x2="6.096" y2="-0.7112" width="0.1524" layer="91"/>
<wire x1="6.096" y1="-0.7112" x2="6.4516" y2="-0.7112" width="0.1524" layer="91"/>
<wire x1="6.096" y1="0.7112" x2="6.096" y2="1.9812" width="0.1524" layer="91"/>
<wire x1="6.096" y1="-0.7112" x2="6.096" y2="-1.9812" width="0.1524" layer="91"/>
<wire x1="6.096" y1="0.7112" x2="5.9436" y2="0.9652" width="0.1524" layer="91"/>
<wire x1="6.096" y1="0.7112" x2="6.1976" y2="0.9652" width="0.1524" layer="91"/>
<wire x1="5.9436" y1="0.9652" x2="6.1976" y2="0.9652" width="0.1524" layer="91"/>
<wire x1="6.096" y1="-0.7112" x2="5.9436" y2="-0.9652" width="0.1524" layer="91"/>
<wire x1="6.096" y1="-0.7112" x2="6.1976" y2="-0.9652" width="0.1524" layer="91"/>
<wire x1="5.9436" y1="-0.9652" x2="6.1976" y2="-0.9652" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<wire x1="-1.0922" y1="0" x2="-1.0922" y2="1.6764" width="0.1524" layer="91"/>
<wire x1="-1.0922" y1="1.6764" x2="-1.0922" y2="2.0828" width="0.1524" layer="91"/>
<wire x1="-1.0922" y1="1.6764" x2="0.1778" y2="1.6764" width="0.1524" layer="91"/>
<wire x1="-1.0922" y1="1.6764" x2="-0.8382" y2="1.8288" width="0.1524" layer="91"/>
<wire x1="-1.0922" y1="1.6764" x2="-0.8382" y2="1.5748" width="0.1524" layer="91"/>
<wire x1="-0.8382" y1="1.8288" x2="-0.8382" y2="1.5748" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<wire x1="-1.1176" y1="-0.8128" x2="1.1176" y2="-0.8128" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<wire x1="1.1176" y1="0.8128" x2="-1.1176" y2="0.8128" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
