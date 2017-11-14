<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="8.4.0">
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
<layer number="51" name="tDocu" color="6" fill="1" visible="no" active="no"/>
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
<library name="analog-devices" urn="urn:adsk.eagle:library:102">
<description>&lt;b&gt;Analog Devices Components&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="DIL16" urn="urn:adsk.eagle:footprint:3757/1" library_version="1">
<description>&lt;b&gt;Dual In Line Package&lt;/b&gt;</description>
<wire x1="10.16" y1="2.921" x2="-10.16" y2="2.921" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-2.921" x2="10.16" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="10.16" y1="2.921" x2="10.16" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="2.921" x2="-10.16" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-2.921" x2="-10.16" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="1.016" x2="-10.16" y2="-1.016" width="0.1524" layer="21" curve="-180"/>
<pad name="1" x="-8.89" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="2" x="-6.35" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="7" x="6.35" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="8" x="8.89" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="3" x="-3.81" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="4" x="-1.27" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="6" x="3.81" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="5" x="1.27" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="9" x="8.89" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="10" x="6.35" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="11" x="3.81" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="12" x="1.27" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="13" x="-1.27" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="14" x="-3.81" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="15" x="-6.35" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="16" x="-8.89" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<text x="-10.541" y="-2.921" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-7.493" y="-0.635" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="SOIC16N" urn="urn:adsk.eagle:footprint:3724/1" library_version="1">
<description>&lt;b&gt;SMALL OUTLINE INTEGRATED CIRCUIT&lt;/b&gt;</description>
<wire x1="4.94" y1="-1.9" x2="-4.94" y2="-1.9" width="0.2032" layer="51"/>
<wire x1="-4.94" y1="-1.9" x2="-4.94" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="-4.94" y1="-1.4" x2="-4.94" y2="1.9" width="0.2032" layer="51"/>
<wire x1="-4.94" y1="1.9" x2="4.94" y2="1.9" width="0.2032" layer="51"/>
<wire x1="4.94" y1="-1.4" x2="-4.94" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="4.94" y1="1.9" x2="4.94" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="4.94" y1="-1.4" x2="4.94" y2="-1.9" width="0.2032" layer="51"/>
<smd name="2" x="-3.175" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="13" x="-0.635" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="1" x="-4.445" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="3" x="-1.905" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="4" x="-0.635" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="14" x="-1.905" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="12" x="0.635" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="11" x="1.905" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="6" x="1.905" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="9" x="4.445" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="5" x="0.635" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="7" x="3.175" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="10" x="3.175" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="8" x="4.445" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="15" x="-3.175" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="16" x="-4.445" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<text x="-5.207" y="-1.905" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="-4.445" y="-0.635" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-4.69" y1="-3.1" x2="-4.2" y2="-2" layer="51"/>
<rectangle x1="-3.42" y1="-3.1" x2="-2.93" y2="-2" layer="51"/>
<rectangle x1="-2.15" y1="-3.1" x2="-1.66" y2="-2" layer="51"/>
<rectangle x1="-0.88" y1="-3.1" x2="-0.39" y2="-2" layer="51"/>
<rectangle x1="1.66" y1="2" x2="2.15" y2="3.1" layer="51"/>
<rectangle x1="0.39" y1="2" x2="0.88" y2="3.1" layer="51"/>
<rectangle x1="-0.88" y1="2" x2="-0.39" y2="3.1" layer="51"/>
<rectangle x1="-2.15" y1="2" x2="-1.66" y2="3.1" layer="51"/>
<rectangle x1="0.39" y1="-3.1" x2="0.88" y2="-2" layer="51"/>
<rectangle x1="1.66" y1="-3.1" x2="2.15" y2="-2" layer="51"/>
<rectangle x1="2.93" y1="-3.1" x2="3.42" y2="-2" layer="51"/>
<rectangle x1="4.2" y1="-3.1" x2="4.69" y2="-2" layer="51"/>
<rectangle x1="4.2" y1="2" x2="4.69" y2="3.1" layer="51"/>
<rectangle x1="2.93" y1="2" x2="3.42" y2="3.1" layer="51"/>
<rectangle x1="-3.42" y1="2" x2="-2.93" y2="3.1" layer="51"/>
<rectangle x1="-4.69" y1="2" x2="-4.2" y2="3.1" layer="51"/>
</package>
<package name="PLCC20" urn="urn:adsk.eagle:footprint:3752/1" library_version="1">
<description>&lt;b&gt;Plastic Leaded Chip Carrier&lt;/b&gt;&lt;p&gt;IPC standard</description>
<wire x1="4.8999" y1="4.8999" x2="-2.665" y2="4.8999" width="0.2032" layer="51"/>
<wire x1="-4.8999" y1="2.665" x2="-4.8999" y2="-4.8999" width="0.2032" layer="51"/>
<wire x1="-4.8999" y1="-4.8999" x2="4.8999" y2="-4.8999" width="0.2032" layer="51"/>
<wire x1="4.8999" y1="-4.8999" x2="4.8999" y2="4.8999" width="0.2032" layer="51"/>
<wire x1="-2.665" y1="4.8999" x2="-4.8999" y2="2.665" width="0.2032" layer="51"/>
<wire x1="-3.173" y1="4.3919" x2="-4.3919" y2="3.173" width="0.2032" layer="21"/>
<wire x1="-4.8999" y1="-3.431" x2="-4.8999" y2="-4.8999" width="0.2032" layer="21"/>
<wire x1="-4.8999" y1="-4.8999" x2="-3.2281" y2="-4.8999" width="0.2032" layer="21"/>
<wire x1="3.431" y1="-4.8999" x2="4.8999" y2="-4.8999" width="0.2032" layer="21"/>
<wire x1="4.8999" y1="-4.8999" x2="4.8999" y2="-3.2281" width="0.2032" layer="21"/>
<wire x1="4.8999" y1="3.431" x2="4.8999" y2="4.8999" width="0.2032" layer="21"/>
<wire x1="4.8999" y1="4.8999" x2="3.2281" y2="4.8999" width="0.2032" layer="21"/>
<circle x="0" y="3.8001" radius="0.3" width="0.6096" layer="51"/>
<smd name="1" x="0" y="4.3" dx="0.5996" dy="2.1998" layer="1"/>
<smd name="2" x="-1.27" y="4.3" dx="0.5996" dy="2.1998" layer="1"/>
<smd name="3" x="-2.54" y="4.3" dx="0.5996" dy="2.1998" layer="1"/>
<smd name="4" x="-4.3" y="2.54" dx="2.1998" dy="0.5996" layer="1"/>
<smd name="5" x="-4.3" y="1.27" dx="2.1998" dy="0.5996" layer="1"/>
<smd name="6" x="-4.3" y="0" dx="2.1998" dy="0.5996" layer="1"/>
<smd name="7" x="-4.3" y="-1.27" dx="2.1998" dy="0.5996" layer="1"/>
<smd name="8" x="-4.3" y="-2.54" dx="2.1998" dy="0.5996" layer="1"/>
<smd name="9" x="-2.54" y="-4.3" dx="0.5996" dy="2.1998" layer="1"/>
<smd name="10" x="-1.27" y="-4.3" dx="0.5996" dy="2.1998" layer="1"/>
<smd name="11" x="0" y="-4.3" dx="0.5996" dy="2.1998" layer="1"/>
<smd name="12" x="1.27" y="-4.3" dx="0.5996" dy="2.1998" layer="1"/>
<smd name="13" x="2.54" y="-4.3" dx="0.5996" dy="2.1998" layer="1"/>
<smd name="14" x="4.3" y="-2.54" dx="2.1998" dy="0.5996" layer="1"/>
<smd name="15" x="4.3" y="-1.27" dx="2.1998" dy="0.5996" layer="1"/>
<smd name="16" x="4.3" y="0" dx="2.1998" dy="0.5996" layer="1"/>
<smd name="17" x="4.3" y="1.27" dx="2.1998" dy="0.5996" layer="1"/>
<smd name="18" x="4.3" y="2.54" dx="2.1998" dy="0.5996" layer="1"/>
<smd name="19" x="2.54" y="4.3" dx="0.5996" dy="2.1998" layer="1"/>
<smd name="20" x="1.27" y="4.3" dx="0.5996" dy="2.1998" layer="1"/>
<text x="-3.81" y="5.715" size="1.778" layer="25">&gt;NAME</text>
<text x="-4.445" y="-7.4851" size="1.778" layer="27">&gt;VALUE</text>
<rectangle x1="-0.2601" y1="4.95" x2="0.2601" y2="5.4" layer="51"/>
<rectangle x1="-1.5301" y1="4.95" x2="-1.0099" y2="5.4" layer="51"/>
<rectangle x1="-2.8001" y1="4.95" x2="-2.2799" y2="5.4" layer="51"/>
<rectangle x1="-5.4" y1="2.2799" x2="-4.95" y2="2.8001" layer="51"/>
<rectangle x1="-5.4" y1="1.0099" x2="-4.95" y2="1.5301" layer="51"/>
<rectangle x1="-5.4" y1="-0.2601" x2="-4.95" y2="0.2601" layer="51"/>
<rectangle x1="-5.4" y1="-1.5301" x2="-4.95" y2="-1.0099" layer="51"/>
<rectangle x1="-5.4" y1="-2.8001" x2="-4.95" y2="-2.2799" layer="51"/>
<rectangle x1="-2.8001" y1="-5.4" x2="-2.2799" y2="-4.95" layer="51"/>
<rectangle x1="-1.5301" y1="-5.4" x2="-1.0099" y2="-4.95" layer="51"/>
<rectangle x1="-0.2601" y1="-5.4" x2="0.2601" y2="-4.95" layer="51"/>
<rectangle x1="1.0099" y1="-5.4" x2="1.5301" y2="-4.95" layer="51"/>
<rectangle x1="2.2799" y1="-5.4" x2="2.8001" y2="-4.95" layer="51"/>
<rectangle x1="4.95" y1="-2.8001" x2="5.4" y2="-2.2799" layer="51"/>
<rectangle x1="4.95" y1="-1.5301" x2="5.4" y2="-1.0099" layer="51"/>
<rectangle x1="4.95" y1="-0.2601" x2="5.4" y2="0.2601" layer="51"/>
<rectangle x1="4.95" y1="1.0099" x2="5.4" y2="1.5301" layer="51"/>
<rectangle x1="4.95" y1="2.2799" x2="5.4" y2="2.8001" layer="51"/>
<rectangle x1="2.2799" y1="4.95" x2="2.8001" y2="5.4" layer="51"/>
<rectangle x1="1.0099" y1="4.95" x2="1.5301" y2="5.4" layer="51"/>
</package>
<package name="LCC20" urn="urn:adsk.eagle:footprint:3719/1" library_version="1">
<description>&lt;b&gt;PLASTIC LEADED CHIP CARRIER&lt;/b&gt;</description>
<wire x1="-0.4" y1="4.4" x2="-0.87" y2="4.4" width="0.2032" layer="51"/>
<wire x1="-3.3" y1="4.4" x2="-4.4" y2="3.3" width="0.2032" layer="51"/>
<wire x1="-0.4" y1="4.3984" x2="0.4" y2="4.3984" width="0.2032" layer="51" curve="180"/>
<wire x1="-1.67" y1="4.3984" x2="-0.87" y2="4.3984" width="0.2032" layer="51" curve="180"/>
<wire x1="-4.3984" y1="2.14" x2="-4.3984" y2="2.94" width="0.2032" layer="51" curve="180"/>
<wire x1="-2.94" y1="4.4" x2="-3.3" y2="4.4" width="0.2032" layer="51"/>
<wire x1="0.87" y1="4.4" x2="0.4" y2="4.4" width="0.2032" layer="51"/>
<wire x1="0.87" y1="4.3984" x2="1.67" y2="4.3984" width="0.2032" layer="51" curve="180"/>
<wire x1="-4.4" y1="3.3" x2="-4.4" y2="2.94" width="0.2032" layer="51"/>
<wire x1="-4.4" y1="2.14" x2="-4.4" y2="1.67" width="0.2032" layer="51"/>
<wire x1="-4.3984" y1="0.87" x2="-4.3984" y2="1.67" width="0.2032" layer="51" curve="180"/>
<wire x1="-4.3984" y1="-0.4" x2="-4.3984" y2="0.4" width="0.2032" layer="51" curve="180"/>
<wire x1="-4.3984" y1="-1.67" x2="-4.3984" y2="-0.87" width="0.2032" layer="51" curve="180"/>
<wire x1="-4.4" y1="0.87" x2="-4.4" y2="0.4" width="0.2032" layer="51"/>
<wire x1="-4.4" y1="-0.4" x2="-4.4" y2="-0.87" width="0.2032" layer="51"/>
<wire x1="-4.4" y1="-2.94" x2="-4.4" y2="-4.4" width="0.2032" layer="51"/>
<wire x1="-4.4" y1="-4.4" x2="-4.4" y2="-4.41" width="0.2032" layer="51"/>
<wire x1="2.14" y1="4.3984" x2="2.94" y2="4.3984" width="0.2032" layer="51" curve="180"/>
<wire x1="2.14" y1="4.4" x2="1.67" y2="4.4" width="0.2032" layer="51"/>
<wire x1="4.4" y1="4.4" x2="2.94" y2="4.4" width="0.2032" layer="51"/>
<wire x1="0.4" y1="-4.4" x2="0.87" y2="-4.4" width="0.2032" layer="51"/>
<wire x1="-0.4" y1="-4.3984" x2="0.4" y2="-4.3984" width="0.2032" layer="51" curve="-180"/>
<wire x1="0.87" y1="-4.3984" x2="1.67" y2="-4.3984" width="0.2032" layer="51" curve="-180"/>
<wire x1="2.94" y1="-4.4" x2="4.4" y2="-4.4" width="0.2032" layer="51"/>
<wire x1="-0.87" y1="-4.4" x2="-0.4" y2="-4.4" width="0.2032" layer="51"/>
<wire x1="-1.67" y1="-4.3984" x2="-0.87" y2="-4.3984" width="0.2032" layer="51" curve="-180"/>
<wire x1="-2.94" y1="-4.3984" x2="-2.14" y2="-4.3984" width="0.2032" layer="51" curve="-180"/>
<wire x1="-2.14" y1="-4.4" x2="-1.67" y2="-4.4" width="0.2032" layer="51"/>
<wire x1="-4.4" y1="-4.4" x2="-2.94" y2="-4.4" width="0.2032" layer="51"/>
<wire x1="4.4" y1="0.4" x2="4.4" y2="0.87" width="0.2032" layer="51"/>
<wire x1="4.3984" y1="0.4" x2="4.3984" y2="-0.4" width="0.2032" layer="51" curve="180"/>
<wire x1="4.3984" y1="1.67" x2="4.3984" y2="0.87" width="0.2032" layer="51" curve="180"/>
<wire x1="4.4" y1="2.94" x2="4.4" y2="4.4" width="0.2032" layer="51"/>
<wire x1="4.4" y1="-0.87" x2="4.4" y2="-0.4" width="0.2032" layer="51"/>
<wire x1="4.3984" y1="-0.87" x2="4.3984" y2="-1.67" width="0.2032" layer="51" curve="180"/>
<wire x1="4.3984" y1="-2.14" x2="4.3984" y2="-2.94" width="0.2032" layer="51" curve="180"/>
<wire x1="4.4" y1="-2.14" x2="4.4" y2="-1.67" width="0.2032" layer="51"/>
<wire x1="4.4" y1="-4.4" x2="4.4" y2="-2.94" width="0.2032" layer="51"/>
<wire x1="-2.94" y1="4.3984" x2="-2.14" y2="4.3984" width="0.2032" layer="51" curve="180"/>
<wire x1="-1.67" y1="4.4" x2="-2.14" y2="4.4" width="0.2032" layer="51"/>
<wire x1="-4.3984" y1="-2.94" x2="-4.3984" y2="-2.14" width="0.2032" layer="51" curve="180"/>
<wire x1="-4.4" y1="-1.67" x2="-4.4" y2="-2.14" width="0.2032" layer="51"/>
<wire x1="1.67" y1="-4.4" x2="2.14" y2="-4.4" width="0.2032" layer="51"/>
<wire x1="2.14" y1="-4.3984" x2="2.94" y2="-4.3984" width="0.2032" layer="51" curve="-180"/>
<wire x1="4.3984" y1="2.94" x2="4.3984" y2="2.14" width="0.2032" layer="51" curve="180"/>
<wire x1="4.4" y1="1.67" x2="4.4" y2="2.14" width="0.2032" layer="51"/>
<smd name="2" x="-1.27" y="4.5" dx="0.8" dy="2" layer="1"/>
<smd name="1" x="0" y="3.8" dx="0.8" dy="3.4" layer="1"/>
<smd name="3" x="-2.54" y="4.5" dx="0.8" dy="2" layer="1"/>
<smd name="4" x="-4.5" y="2.54" dx="2" dy="0.8" layer="1"/>
<smd name="5" x="-4.5" y="1.27" dx="2" dy="0.8" layer="1"/>
<smd name="6" x="-4.5" y="0" dx="2" dy="0.8" layer="1"/>
<smd name="7" x="-4.5" y="-1.27" dx="2" dy="0.8" layer="1"/>
<smd name="8" x="-4.5" y="-2.54" dx="2" dy="0.8" layer="1"/>
<smd name="9" x="-2.54" y="-4.5" dx="0.8" dy="2" layer="1"/>
<smd name="10" x="-1.27" y="-4.5" dx="0.8" dy="2" layer="1"/>
<smd name="11" x="0" y="-4.5" dx="0.8" dy="2" layer="1"/>
<smd name="12" x="1.27" y="-4.5" dx="0.8" dy="2" layer="1"/>
<smd name="13" x="2.54" y="-4.5" dx="0.8" dy="2" layer="1"/>
<smd name="14" x="4.5" y="-2.54" dx="2" dy="0.8" layer="1"/>
<smd name="15" x="4.5" y="-1.27" dx="2" dy="0.8" layer="1"/>
<smd name="16" x="4.5" y="0" dx="2" dy="0.8" layer="1"/>
<smd name="17" x="4.5" y="1.27" dx="2" dy="0.8" layer="1"/>
<smd name="18" x="4.5" y="2.54" dx="2" dy="0.8" layer="1"/>
<smd name="19" x="2.54" y="4.5" dx="0.8" dy="2" layer="1"/>
<smd name="20" x="1.27" y="4.5" dx="0.8" dy="2" layer="1"/>
<text x="-4.005" y="6.065" size="1.778" layer="25">&gt;NAME</text>
<text x="-3.975" y="-8.195" size="1.778" layer="27">&gt;VALUE</text>
<text x="-0.635" y="0.635" size="1.27" layer="21">1</text>
</package>
</packages>
<packages3d>
<package3d name="DIL16" urn="urn:adsk.eagle:package:3925/1" type="box" library_version="1">
<description>Dual In Line Package</description>
</package3d>
<package3d name="SOIC16N" urn="urn:adsk.eagle:package:3918/1" type="box" library_version="1">
<description>SMALL OUTLINE INTEGRATED CIRCUIT</description>
</package3d>
<package3d name="PLCC20" urn="urn:adsk.eagle:package:3927/1" type="box" library_version="1">
<description>Plastic Leaded Chip CarrierIPC standard</description>
</package3d>
<package3d name="LCC20" urn="urn:adsk.eagle:package:3916/1" type="box" library_version="1">
<description>PLASTIC LEADED CHIP CARRIER</description>
</package3d>
</packages3d>
<symbols>
<symbol name="AD7524" urn="urn:adsk.eagle:symbol:3756/1" library_version="1">
<wire x1="-10.16" y1="15.24" x2="10.16" y2="15.24" width="0.254" layer="94"/>
<wire x1="10.16" y1="15.24" x2="10.16" y2="-15.24" width="0.254" layer="94"/>
<wire x1="10.16" y1="-15.24" x2="-10.16" y2="-15.24" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-15.24" x2="-10.16" y2="15.24" width="0.254" layer="94"/>
<text x="-10.16" y="16.51" size="1.778" layer="95">&gt;NAME</text>
<text x="-10.16" y="-17.78" size="1.778" layer="96">&gt;VALUE</text>
<pin name="VREF" x="12.7" y="7.62" length="short" direction="in" rot="R180"/>
<pin name="VDD" x="12.7" y="12.7" length="short" direction="pwr" rot="R180"/>
<pin name="!CS" x="-12.7" y="12.7" length="short" direction="in"/>
<pin name="!WR" x="-12.7" y="10.16" length="short" direction="in"/>
<pin name="D0" x="-12.7" y="5.08" length="short" direction="in"/>
<pin name="D1" x="-12.7" y="2.54" length="short" direction="in"/>
<pin name="D2" x="-12.7" y="0" length="short" direction="in"/>
<pin name="D3" x="-12.7" y="-2.54" length="short" direction="in"/>
<pin name="D4" x="-12.7" y="-5.08" length="short" direction="in"/>
<pin name="D5" x="-12.7" y="-7.62" length="short" direction="in"/>
<pin name="D6" x="-12.7" y="-10.16" length="short" direction="in"/>
<pin name="D7" x="-12.7" y="-12.7" length="short" direction="in"/>
<pin name="RFB" x="12.7" y="2.54" length="short" direction="pas" rot="R180"/>
<pin name="OUT1" x="12.7" y="-2.54" length="short" direction="pas" rot="R180"/>
<pin name="OUT2" x="12.7" y="-7.62" length="short" direction="pas" rot="R180"/>
<pin name="GND" x="12.7" y="-12.7" length="short" direction="pwr" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="AD7524*" urn="urn:adsk.eagle:component:4030/1" prefix="IC" library_version="1">
<description>&lt;b&gt;8-Bit Buffered Multiplying DAC&lt;/b&gt;&lt;p&gt;
Source: http://www.analog.com/UploadedFiles/Data_Sheets/888358036ad7524.pdf</description>
<gates>
<gate name="G$1" symbol="AD7524" x="0" y="0"/>
</gates>
<devices>
<device name="N" package="DIL16">
<connects>
<connect gate="G$1" pin="!CS" pad="12"/>
<connect gate="G$1" pin="!WR" pad="13"/>
<connect gate="G$1" pin="D0" pad="11"/>
<connect gate="G$1" pin="D1" pad="10"/>
<connect gate="G$1" pin="D2" pad="9"/>
<connect gate="G$1" pin="D3" pad="8"/>
<connect gate="G$1" pin="D4" pad="7"/>
<connect gate="G$1" pin="D5" pad="6"/>
<connect gate="G$1" pin="D6" pad="5"/>
<connect gate="G$1" pin="D7" pad="4"/>
<connect gate="G$1" pin="GND" pad="3"/>
<connect gate="G$1" pin="OUT1" pad="1"/>
<connect gate="G$1" pin="OUT2" pad="2"/>
<connect gate="G$1" pin="RFB" pad="16"/>
<connect gate="G$1" pin="VDD" pad="14"/>
<connect gate="G$1" pin="VREF" pad="15"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:3925/1"/>
</package3dinstances>
<technologies>
<technology name="J">
<attribute name="MF" value="ALTERA CORPORATION" constant="no"/>
<attribute name="MPN" value="AD7524JNZ" constant="no"/>
<attribute name="OC_FARNELL" value="9605401" constant="no"/>
<attribute name="OC_NEWARK" value="59K4969" constant="no"/>
</technology>
<technology name="K">
<attribute name="MF" value="ALTERA CORPORATION" constant="no"/>
<attribute name="MPN" value="AD7524KNZ" constant="no"/>
<attribute name="OC_FARNELL" value="1464568" constant="no"/>
<attribute name="OC_NEWARK" value="59K4973" constant="no"/>
</technology>
<technology name="L">
<attribute name="MF" value="ALTERA CORPORATION" constant="no"/>
<attribute name="MPN" value="AD7524LNZ" constant="no"/>
<attribute name="OC_FARNELL" value="9605401" constant="no"/>
<attribute name="OC_NEWARK" value="59K4974" constant="no"/>
</technology>
</technologies>
</device>
<device name="R" package="SOIC16N">
<connects>
<connect gate="G$1" pin="!CS" pad="12"/>
<connect gate="G$1" pin="!WR" pad="13"/>
<connect gate="G$1" pin="D0" pad="11"/>
<connect gate="G$1" pin="D1" pad="10"/>
<connect gate="G$1" pin="D2" pad="9"/>
<connect gate="G$1" pin="D3" pad="8"/>
<connect gate="G$1" pin="D4" pad="7"/>
<connect gate="G$1" pin="D5" pad="6"/>
<connect gate="G$1" pin="D6" pad="5"/>
<connect gate="G$1" pin="D7" pad="4"/>
<connect gate="G$1" pin="GND" pad="3"/>
<connect gate="G$1" pin="OUT1" pad="1"/>
<connect gate="G$1" pin="OUT2" pad="2"/>
<connect gate="G$1" pin="RFB" pad="16"/>
<connect gate="G$1" pin="VDD" pad="14"/>
<connect gate="G$1" pin="VREF" pad="15"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:3918/1"/>
</package3dinstances>
<technologies>
<technology name="J">
<attribute name="MF" value="ALTERA CORPORATION" constant="no"/>
<attribute name="MPN" value="AD7524JRZ" constant="no"/>
<attribute name="OC_FARNELL" value="1423882" constant="no"/>
<attribute name="OC_NEWARK" value="59K4970" constant="no"/>
</technology>
</technologies>
</device>
<device name="P" package="PLCC20">
<connects>
<connect gate="G$1" pin="!CS" pad="15"/>
<connect gate="G$1" pin="!WR" pad="17"/>
<connect gate="G$1" pin="D0" pad="14"/>
<connect gate="G$1" pin="D1" pad="13"/>
<connect gate="G$1" pin="D2" pad="12"/>
<connect gate="G$1" pin="D3" pad="10"/>
<connect gate="G$1" pin="D4" pad="9"/>
<connect gate="G$1" pin="D5" pad="8"/>
<connect gate="G$1" pin="D6" pad="7"/>
<connect gate="G$1" pin="D7" pad="5"/>
<connect gate="G$1" pin="GND" pad="4"/>
<connect gate="G$1" pin="OUT1" pad="2"/>
<connect gate="G$1" pin="OUT2" pad="3"/>
<connect gate="G$1" pin="RFB" pad="20"/>
<connect gate="G$1" pin="VDD" pad="18"/>
<connect gate="G$1" pin="VREF" pad="19"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:3927/1"/>
</package3dinstances>
<technologies>
<technology name="J">
<attribute name="MF" value="ALTERA CORPORATION" constant="no"/>
<attribute name="MPN" value="AD7524JP" constant="no"/>
<attribute name="OC_FARNELL" value="1464569" constant="no"/>
<attribute name="OC_NEWARK" value="05F7382" constant="no"/>
</technology>
<technology name="K">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="1464569" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
<technology name="L">
<attribute name="MF" value="ALTERA CORPORATION" constant="no"/>
<attribute name="MPN" value="AD7524LP" constant="no"/>
<attribute name="OC_FARNELL" value="1464569" constant="no"/>
<attribute name="OC_NEWARK" value="09B5765" constant="no"/>
</technology>
</technologies>
</device>
<device name="E" package="LCC20">
<connects>
<connect gate="G$1" pin="!CS" pad="15"/>
<connect gate="G$1" pin="!WR" pad="17"/>
<connect gate="G$1" pin="D0" pad="14"/>
<connect gate="G$1" pin="D1" pad="13"/>
<connect gate="G$1" pin="D2" pad="12"/>
<connect gate="G$1" pin="D3" pad="10"/>
<connect gate="G$1" pin="D4" pad="9"/>
<connect gate="G$1" pin="D5" pad="8"/>
<connect gate="G$1" pin="D6" pad="7"/>
<connect gate="G$1" pin="D7" pad="5"/>
<connect gate="G$1" pin="GND" pad="4"/>
<connect gate="G$1" pin="OUT1" pad="2"/>
<connect gate="G$1" pin="OUT2" pad="3"/>
<connect gate="G$1" pin="RFB" pad="20"/>
<connect gate="G$1" pin="VDD" pad="18"/>
<connect gate="G$1" pin="VREF" pad="19"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:3916/1"/>
</package3dinstances>
<technologies>
<technology name="S">
<attribute name="MF" value="ALTERA CORPORATION" constant="no"/>
<attribute name="MPN" value="AD7524JP" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="05F7382" constant="no"/>
</technology>
<technology name="T">
<attribute name="MF" value="ALTERA CORPORATION" constant="no"/>
<attribute name="MPN" value="AD7524JP" constant="no"/>
<attribute name="OC_FARNELL" value="1464569" constant="no"/>
<attribute name="OC_NEWARK" value="05F7382" constant="no"/>
</technology>
<technology name="U">
<attribute name="MF" value="ALTERA CORPORATION" constant="no"/>
<attribute name="MPN" value="AD7524KP" constant="no"/>
<attribute name="OC_FARNELL" value="1464569" constant="no"/>
<attribute name="OC_NEWARK" value="09B5764" constant="no"/>
</technology>
</technologies>
</device>
<device name="Q" package="DIL16">
<connects>
<connect gate="G$1" pin="!CS" pad="12"/>
<connect gate="G$1" pin="!WR" pad="13"/>
<connect gate="G$1" pin="D0" pad="11"/>
<connect gate="G$1" pin="D1" pad="10"/>
<connect gate="G$1" pin="D2" pad="9"/>
<connect gate="G$1" pin="D3" pad="8"/>
<connect gate="G$1" pin="D4" pad="7"/>
<connect gate="G$1" pin="D5" pad="6"/>
<connect gate="G$1" pin="D6" pad="5"/>
<connect gate="G$1" pin="D7" pad="4"/>
<connect gate="G$1" pin="GND" pad="3"/>
<connect gate="G$1" pin="OUT1" pad="1"/>
<connect gate="G$1" pin="OUT2" pad="2"/>
<connect gate="G$1" pin="RFB" pad="16"/>
<connect gate="G$1" pin="VDD" pad="14"/>
<connect gate="G$1" pin="VREF" pad="15"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:3925/1"/>
</package3dinstances>
<technologies>
<technology name="A">
<attribute name="MF" value="ALTERA CORPORATION" constant="no"/>
<attribute name="MPN" value="AD7524AQ" constant="no"/>
<attribute name="OC_FARNELL" value="1464568" constant="no"/>
<attribute name="OC_NEWARK" value="05F7379" constant="no"/>
</technology>
<technology name="B">
<attribute name="MF" value="ALTERA CORPORATION" constant="no"/>
<attribute name="MPN" value="AD7524KP" constant="no"/>
<attribute name="OC_FARNELL" value="9605401" constant="no"/>
<attribute name="OC_NEWARK" value="09B5764" constant="no"/>
</technology>
<technology name="C">
<attribute name="MF" value="ALTERA CORPORATION" constant="no"/>
<attribute name="MPN" value="AD7524TQ" constant="no"/>
<attribute name="OC_FARNELL" value="1523901" constant="no"/>
<attribute name="OC_NEWARK" value="16F3371" constant="no"/>
</technology>
<technology name="S">
<attribute name="MF" value="ALTERA CORPORATION" constant="no"/>
<attribute name="MPN" value="AD7524SQ" constant="no"/>
<attribute name="OC_FARNELL" value="9605401" constant="no"/>
<attribute name="OC_NEWARK" value="16F3370" constant="no"/>
</technology>
<technology name="T">
<attribute name="MF" value="ALTERA CORPORATION" constant="no"/>
<attribute name="MPN" value="AD7524TQ" constant="no"/>
<attribute name="OC_FARNELL" value="9605401" constant="no"/>
<attribute name="OC_NEWARK" value="16F3371" constant="no"/>
</technology>
<technology name="U">
<attribute name="MF" value="ALTERA CORPORATION" constant="no"/>
<attribute name="MPN" value="AD7524SQ" constant="no"/>
<attribute name="OC_FARNELL" value="1523901" constant="no"/>
<attribute name="OC_NEWARK" value="16F3370" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1" urn="urn:adsk.eagle:library:371">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="GND" urn="urn:adsk.eagle:symbol:26925/1" library_version="1">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" urn="urn:adsk.eagle:component:26954/1" prefix="GND" library_version="1">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply2" urn="urn:adsk.eagle:library:372">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
Please keep in mind, that these devices are necessary for the
automatic wiring of the supply signals.&lt;p&gt;
The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="VCC" urn="urn:adsk.eagle:symbol:26997/1" library_version="2">
<circle x="0" y="1.27" radius="1.27" width="0.254" layer="94"/>
<text x="-1.905" y="3.175" size="1.778" layer="96">&gt;VALUE</text>
<pin name="VCC" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="VCC" urn="urn:adsk.eagle:component:27060/1" prefix="SUPPLY" library_version="2">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="VCC" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="linear" urn="urn:adsk.eagle:library:262">
<description>&lt;b&gt;Linear Devices&lt;/b&gt;&lt;p&gt;
Operational amplifiers,  comparators, voltage regulators, ADCs, DACs, etc.&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="DIL14" urn="urn:adsk.eagle:footprint:16136/1" library_version="2">
<description>&lt;b&gt;Dual In Line Package&lt;/b&gt;</description>
<wire x1="8.89" y1="2.921" x2="-8.89" y2="2.921" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="-2.921" x2="8.89" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="8.89" y1="2.921" x2="8.89" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="2.921" x2="-8.89" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="-2.921" x2="-8.89" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="1.016" x2="-8.89" y2="-1.016" width="0.1524" layer="21" curve="-180"/>
<pad name="1" x="-7.62" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="2" x="-5.08" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="7" x="7.62" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="8" x="7.62" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="3" x="-2.54" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="4" x="0" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="6" x="5.08" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="5" x="2.54" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="9" x="5.08" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="10" x="2.54" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="11" x="0" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="12" x="-2.54" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="13" x="-5.08" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="14" x="-7.62" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<text x="-9.271" y="-3.048" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-6.731" y="-0.635" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="SO14" urn="urn:adsk.eagle:footprint:16137/1" library_version="2">
<description>&lt;b&gt;Small Outline Package 14&lt;/b&gt;</description>
<wire x1="4.305" y1="-1.9" x2="-4.305" y2="-1.9" width="0.2032" layer="51"/>
<wire x1="-4.305" y1="-1.9" x2="-4.305" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="-4.305" y1="-1.4" x2="-4.305" y2="1.9" width="0.2032" layer="51"/>
<wire x1="4.305" y1="-1.4" x2="-4.305" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="4.305" y1="1.9" x2="4.305" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="4.305" y1="-1.4" x2="4.305" y2="-1.9" width="0.2032" layer="51"/>
<wire x1="-4.305" y1="1.9" x2="4.305" y2="1.9" width="0.2032" layer="51"/>
<smd name="2" x="-2.54" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="13" x="-2.54" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="1" x="-3.81" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="3" x="-1.27" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="4" x="0" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="14" x="-3.81" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="12" x="-1.27" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="11" x="0" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="6" x="2.54" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="9" x="2.54" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="5" x="1.27" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="7" x="3.81" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="10" x="1.27" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="8" x="3.81" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<text x="-4.572" y="-1.905" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="5.842" y="-1.905" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-4.055" y1="-3.1" x2="-3.565" y2="-2" layer="51"/>
<rectangle x1="-2.785" y1="-3.1" x2="-2.295" y2="-2" layer="51"/>
<rectangle x1="-1.515" y1="-3.1" x2="-1.025" y2="-2" layer="51"/>
<rectangle x1="-0.245" y1="-3.1" x2="0.245" y2="-2" layer="51"/>
<rectangle x1="-0.245" y1="2" x2="0.245" y2="3.1" layer="51"/>
<rectangle x1="-1.515" y1="2" x2="-1.025" y2="3.1" layer="51"/>
<rectangle x1="-2.785" y1="2" x2="-2.295" y2="3.1" layer="51"/>
<rectangle x1="-4.055" y1="2" x2="-3.565" y2="3.1" layer="51"/>
<rectangle x1="1.025" y1="-3.1" x2="1.515" y2="-2" layer="51"/>
<rectangle x1="2.295" y1="-3.1" x2="2.785" y2="-2" layer="51"/>
<rectangle x1="3.565" y1="-3.1" x2="4.055" y2="-2" layer="51"/>
<rectangle x1="3.565" y1="2" x2="4.055" y2="3.1" layer="51"/>
<rectangle x1="2.295" y1="2" x2="2.785" y2="3.1" layer="51"/>
<rectangle x1="1.025" y1="2" x2="1.515" y2="3.1" layer="51"/>
</package>
</packages>
<packages3d>
<package3d name="DIL14" urn="urn:adsk.eagle:package:16407/2" type="model" library_version="2">
<description>Dual In Line Package</description>
</package3d>
<package3d name="SO14" urn="urn:adsk.eagle:package:16406/2" type="model" library_version="2">
<description>Small Outline Package 14</description>
</package3d>
</packages3d>
<symbols>
<symbol name="OPAMP" urn="urn:adsk.eagle:symbol:16134/1" library_version="2">
<wire x1="-5.08" y1="5.08" x2="-5.08" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="5.08" y2="0" width="0.4064" layer="94"/>
<wire x1="5.08" y1="0" x2="-5.08" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-3.81" y1="3.175" x2="-3.81" y2="1.905" width="0.1524" layer="94"/>
<wire x1="-4.445" y1="2.54" x2="-3.175" y2="2.54" width="0.1524" layer="94"/>
<wire x1="-4.445" y1="-2.54" x2="-3.175" y2="-2.54" width="0.1524" layer="94"/>
<text x="2.54" y="3.175" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<pin name="-IN" x="-7.62" y="-2.54" visible="pad" length="short" direction="in"/>
<pin name="+IN" x="-7.62" y="2.54" visible="pad" length="short" direction="in"/>
<pin name="OUT" x="7.62" y="0" visible="pad" length="short" direction="out" rot="R180"/>
</symbol>
<symbol name="PWR+-" urn="urn:adsk.eagle:symbol:16135/1" library_version="2">
<text x="1.27" y="3.175" size="0.8128" layer="93" rot="R90">V+</text>
<text x="1.27" y="-4.445" size="0.8128" layer="93" rot="R90">V-</text>
<pin name="V+" x="0" y="7.62" visible="pad" length="middle" direction="pwr" rot="R270"/>
<pin name="V-" x="0" y="-7.62" visible="pad" length="middle" direction="pwr" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="LM324" urn="urn:adsk.eagle:component:16537/4" prefix="IC" library_version="2">
<description>&lt;b&gt;OP AMP&lt;/b&gt;</description>
<gates>
<gate name="A" symbol="OPAMP" x="15.24" y="10.16" swaplevel="1"/>
<gate name="B" symbol="OPAMP" x="43.18" y="10.16" swaplevel="1"/>
<gate name="C" symbol="OPAMP" x="15.24" y="-10.16" swaplevel="1"/>
<gate name="D" symbol="OPAMP" x="43.18" y="-7.62" swaplevel="1"/>
<gate name="P" symbol="PWR+-" x="15.24" y="10.16" addlevel="request"/>
</gates>
<devices>
<device name="N" package="DIL14">
<connects>
<connect gate="A" pin="+IN" pad="3"/>
<connect gate="A" pin="-IN" pad="2"/>
<connect gate="A" pin="OUT" pad="1"/>
<connect gate="B" pin="+IN" pad="5"/>
<connect gate="B" pin="-IN" pad="6"/>
<connect gate="B" pin="OUT" pad="7"/>
<connect gate="C" pin="+IN" pad="10"/>
<connect gate="C" pin="-IN" pad="9"/>
<connect gate="C" pin="OUT" pad="8"/>
<connect gate="D" pin="+IN" pad="12"/>
<connect gate="D" pin="-IN" pad="13"/>
<connect gate="D" pin="OUT" pad="14"/>
<connect gate="P" pin="V+" pad="4"/>
<connect gate="P" pin="V-" pad="11"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16407/2"/>
</package3dinstances>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="D" package="SO14">
<connects>
<connect gate="A" pin="+IN" pad="3"/>
<connect gate="A" pin="-IN" pad="2"/>
<connect gate="A" pin="OUT" pad="1"/>
<connect gate="B" pin="+IN" pad="5"/>
<connect gate="B" pin="-IN" pad="6"/>
<connect gate="B" pin="OUT" pad="7"/>
<connect gate="C" pin="+IN" pad="10"/>
<connect gate="C" pin="-IN" pad="9"/>
<connect gate="C" pin="OUT" pad="8"/>
<connect gate="D" pin="+IN" pad="12"/>
<connect gate="D" pin="-IN" pad="13"/>
<connect gate="D" pin="OUT" pad="14"/>
<connect gate="P" pin="V+" pad="4"/>
<connect gate="P" pin="V-" pad="11"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16406/2"/>
</package3dinstances>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="docu-dummy" urn="urn:adsk.eagle:library:215">
<description>Dummy symbols</description>
<packages>
</packages>
<symbols>
<symbol name="RESISTOR" urn="urn:adsk.eagle:symbol:13162/1" library_version="1">
<wire x1="-2.54" y1="-0.889" x2="2.54" y2="-0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="-0.889" x2="2.54" y2="0" width="0.254" layer="94"/>
<wire x1="2.54" y1="0" x2="2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-0.889" x2="-2.54" y2="0" width="0.254" layer="94"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="-5.08" y1="0" x2="-2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="2.54" y1="0" x2="5.08" y2="0" width="0.1524" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="R" urn="urn:adsk.eagle:component:13171/1" prefix="R" library_version="1">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="RESISTOR" x="0" y="0"/>
</gates>
<devices>
<device name="">
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
<part name="IC1" library="analog-devices" library_urn="urn:adsk.eagle:library:102" deviceset="AD7524*" device="Q" package3d_urn="urn:adsk.eagle:package:3925/1" technology="A"/>
<part name="GND1" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="SUPPLY1" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="VCC" device=""/>
<part name="IC2" library="linear" library_urn="urn:adsk.eagle:library:262" deviceset="LM324" device="N" package3d_urn="urn:adsk.eagle:package:16407/2"/>
<part name="R1" library="docu-dummy" library_urn="urn:adsk.eagle:library:215" deviceset="R" device=""/>
<part name="R2" library="docu-dummy" library_urn="urn:adsk.eagle:library:215" deviceset="R" device=""/>
<part name="R3" library="docu-dummy" library_urn="urn:adsk.eagle:library:215" deviceset="R" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="IC1" gate="G$1" x="55.88" y="71.12"/>
<instance part="GND1" gate="1" x="86.36" y="55.88"/>
<instance part="SUPPLY1" gate="G$1" x="99.06" y="99.06"/>
<instance part="IC2" gate="A" x="124.46" y="83.82"/>
<instance part="IC2" gate="B" x="149.86" y="83.82"/>
<instance part="IC2" gate="C" x="124.46" y="60.96"/>
<instance part="IC2" gate="D" x="149.86" y="60.96"/>
<instance part="IC2" gate="P" x="104.14" y="73.66"/>
<instance part="R1" gate="G$1" x="157.48" y="43.18"/>
<instance part="R2" gate="G$1" x="142.24" y="43.18"/>
<instance part="R3" gate="G$1" x="129.54" y="35.56"/>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="OUT2"/>
<pinref part="GND1" gate="1" pin="GND"/>
<wire x1="68.58" y1="63.5" x2="86.36" y2="63.5" width="0.1524" layer="91"/>
<wire x1="86.36" y1="63.5" x2="86.36" y2="58.42" width="0.1524" layer="91"/>
<pinref part="IC2" gate="P" pin="V-"/>
<wire x1="104.14" y1="66.04" x2="86.36" y2="66.04" width="0.1524" layer="91"/>
<wire x1="86.36" y1="66.04" x2="86.36" y2="63.5" width="0.1524" layer="91"/>
<junction x="86.36" y="63.5"/>
<pinref part="IC2" gate="A" pin="+IN"/>
<wire x1="104.14" y1="66.04" x2="116.84" y2="66.04" width="0.1524" layer="91"/>
<wire x1="116.84" y1="66.04" x2="116.84" y2="86.36" width="0.1524" layer="91"/>
<junction x="104.14" y="66.04"/>
<pinref part="IC2" gate="C" pin="+IN"/>
<wire x1="104.14" y1="63.5" x2="116.84" y2="63.5" width="0.1524" layer="91"/>
<pinref part="IC2" gate="B" pin="+IN"/>
<wire x1="104.14" y1="66.04" x2="142.24" y2="66.04" width="0.1524" layer="91"/>
<wire x1="142.24" y1="66.04" x2="142.24" y2="86.36" width="0.1524" layer="91"/>
<pinref part="IC2" gate="D" pin="+IN"/>
<wire x1="104.14" y1="66.04" x2="104.14" y2="63.5" width="0.1524" layer="91"/>
<wire x1="116.84" y1="63.5" x2="142.24" y2="63.5" width="0.1524" layer="91"/>
</segment>
</net>
<net name="VCC" class="0">
<segment>
<pinref part="SUPPLY1" gate="G$1" pin="VCC"/>
<pinref part="IC1" gate="G$1" pin="VDD"/>
<wire x1="99.06" y1="96.52" x2="99.06" y2="83.82" width="0.1524" layer="91"/>
<wire x1="99.06" y1="83.82" x2="68.58" y2="83.82" width="0.1524" layer="91"/>
<pinref part="IC2" gate="P" pin="V+"/>
<wire x1="104.14" y1="81.28" x2="104.14" y2="83.82" width="0.1524" layer="91"/>
<wire x1="104.14" y1="83.82" x2="99.06" y2="83.82" width="0.1524" layer="91"/>
<junction x="99.06" y="83.82"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="OUT1"/>
<wire x1="68.58" y1="68.58" x2="93.98" y2="68.58" width="0.1524" layer="91"/>
<pinref part="IC2" gate="C" pin="-IN"/>
<wire x1="93.98" y1="68.58" x2="93.98" y2="58.42" width="0.1524" layer="91"/>
<wire x1="93.98" y1="58.42" x2="116.84" y2="58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="RFB"/>
<wire x1="68.58" y1="73.66" x2="137.16" y2="73.66" width="0.1524" layer="91"/>
<wire x1="137.16" y1="73.66" x2="137.16" y2="60.96" width="0.1524" layer="91"/>
<pinref part="IC2" gate="C" pin="OUT"/>
<wire x1="137.16" y1="60.96" x2="132.08" y2="60.96" width="0.1524" layer="91"/>
<wire x1="137.16" y1="60.96" x2="137.16" y2="43.18" width="0.1524" layer="91"/>
<junction x="137.16" y="60.96"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<wire x1="147.32" y1="50.8" x2="139.7" y2="50.8" width="0.1524" layer="91"/>
<wire x1="139.7" y1="50.8" x2="139.7" y2="58.42" width="0.1524" layer="91"/>
<pinref part="IC2" gate="D" pin="-IN"/>
<wire x1="139.7" y1="58.42" x2="142.24" y2="58.42" width="0.1524" layer="91"/>
<wire x1="147.32" y1="50.8" x2="147.32" y2="43.18" width="0.1524" layer="91"/>
<wire x1="147.32" y1="43.18" x2="147.32" y2="35.56" width="0.1524" layer="91"/>
<wire x1="147.32" y1="35.56" x2="134.62" y2="35.56" width="0.1524" layer="91"/>
<wire x1="147.32" y1="43.18" x2="152.4" y2="43.18" width="0.1524" layer="91"/>
<junction x="147.32" y="43.18"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<wire x1="124.46" y1="35.56" x2="96.52" y2="35.56" width="0.1524" layer="91"/>
<wire x1="96.52" y1="35.56" x2="96.52" y2="78.74" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="VREF"/>
<wire x1="96.52" y1="78.74" x2="68.58" y2="78.74" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="IC2" gate="D" pin="OUT"/>
<wire x1="162.56" y1="43.18" x2="162.56" y2="60.96" width="0.1524" layer="91"/>
<wire x1="162.56" y1="60.96" x2="157.48" y2="60.96" width="0.1524" layer="91"/>
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
