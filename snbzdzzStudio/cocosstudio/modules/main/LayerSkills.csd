<GameProjectFile>
  <PropertyGroup Type="Layer" Name="LayerSkills" ID="34d8143e-97c6-412d-9290-3e2b473c4a20" Version="2.3.2.3" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="LayerSkills" Tag="90" ctype="GameLayerObjectData">
        <Size X="640.0000" Y="960.0000" />
        <Children>
          <AbstractNodeData Name="spriteBg" ActionTag="-1418609973" Tag="51" IconVisible="False" HorizontalEdge="BothEdge" VerticalEdge="BothEdge" ctype="SpriteObjectData">
            <Size X="640.0000" Y="960.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="320.0000" Y="480.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.0000" Y="1.0000" />
            <FileData Type="Normal" Path="images/bg/bg.png" Plist="" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="layoutMaid" ActionTag="-1782727080" Tag="52" IconVisible="False" BackColorAlpha="0" ColorAngle="90.0000" ctype="PanelObjectData">
            <Size X="640.0000" Y="960.0000" />
            <Children>
              <AbstractNodeData Name="spriteBuyTip" ActionTag="1310964043" Tag="54" IconVisible="False" LeftMargin="232.5000" RightMargin="232.5000" TopMargin="406.0000" BottomMargin="486.0000" ctype="SpriteObjectData">
                <Size X="175.0000" Y="68.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="320.0000" Y="520.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5417" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="MarkedSubImage" Path="images/girl/buy1.png" Plist="modules/main/PlistMain.plist" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="spriteNameBg" ActionTag="1881748643" Tag="57" IconVisible="False" LeftMargin="235.0000" RightMargin="235.0000" TopMargin="759.0000" BottomMargin="159.0000" ctype="SpriteObjectData">
                <Size X="170.0000" Y="42.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="320.0000" Y="180.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.1875" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="MarkedSubImage" Path="images/girl/role_name.png" Plist="modules/main/PlistMain.plist" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="btnPrev" ActionTag="-1233900949" Tag="213" IconVisible="False" LeftMargin="96.5000" RightMargin="436.5000" TopMargin="700.5000" BottomMargin="180.5000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="77" Scale9Height="57" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="107.0000" Y="79.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="150.0000" Y="220.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.2344" Y="0.2292" />
                <PreSize X="0.1672" Y="0.0823" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="MarkedSubImage" Path="images/girl/left.png" Plist="modules/main/PlistMain.plist" />
                <NormalFileData Type="MarkedSubImage" Path="images/girl/left.png" Plist="modules/main/PlistMain.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btnNext" ActionTag="-1243916847" Tag="214" IconVisible="False" LeftMargin="430.0000" RightMargin="90.0000" TopMargin="694.0000" BottomMargin="174.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="90" Scale9Height="70" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="120.0000" Y="92.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="490.0000" Y="220.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7656" Y="0.2292" />
                <PreSize X="0.1875" Y="0.0958" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="MarkedSubImage" Path="images/girl/right.png" Plist="modules/main/PlistMain.plist" />
                <NormalFileData Type="MarkedSubImage" Path="images/girl/right.png" Plist="modules/main/PlistMain.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btnSkill" ActionTag="490180091" Tag="48" IconVisible="False" LeftMargin="527.5000" RightMargin="7.5000" TopMargin="217.0000" BottomMargin="617.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="75" Scale9Height="104" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="105.0000" Y="126.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="580.0000" Y="680.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.9063" Y="0.7083" />
                <PreSize X="0.1641" Y="0.1312" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="MarkedSubImage" Path="images/girl/skill.png" Plist="modules/main/PlistMain.plist" />
                <NormalFileData Type="MarkedSubImage" Path="images/girl/skill.png" Plist="modules/main/PlistMain.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="layoutSkillItems" ActionTag="-573801320" VisibleForFrame="False" Tag="998" IconVisible="False" BackColorAlpha="0" ColorAngle="90.0000" ctype="PanelObjectData">
            <Size X="640.0000" Y="960.0000" />
            <Children>
              <AbstractNodeData Name="spriteBg" ActionTag="32141392" Tag="999" IconVisible="False" LeftMargin="-18.5000" RightMargin="-18.5000" TopMargin="-36.0000" BottomMargin="56.0000" ctype="SpriteObjectData">
                <Size X="677.0000" Y="940.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="320.0000" Y="526.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5479" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="images/skills_panel/bg2.png" Plist="" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="spriteIcon" ActionTag="1909835061" Tag="1000" IconVisible="False" LeftMargin="35.0000" RightMargin="515.0000" TopMargin="35.0000" BottomMargin="835.0000" ctype="SpriteObjectData">
                <Size X="90.0000" Y="90.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="80.0000" Y="880.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.1250" Y="0.9167" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="images/skills_panel/zhiye.png" Plist="" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="spriteName" ActionTag="1127073709" Tag="1001" IconVisible="False" LeftMargin="138.0000" RightMargin="346.0000" TopMargin="46.0000" BottomMargin="846.0000" ctype="SpriteObjectData">
                <Size X="156.0000" Y="68.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="216.0000" Y="880.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.3375" Y="0.9167" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="images/skills_panel/name button.png" Plist="" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="spriteSkillDesc" ActionTag="1389928227" Tag="1002" IconVisible="False" LeftMargin="312.5000" RightMargin="104.5000" TopMargin="45.0000" BottomMargin="857.0000" ctype="SpriteObjectData">
                <Size X="223.0000" Y="58.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="424.0000" Y="886.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.6625" Y="0.9229" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="images/skills_panel/Skills button.png" Plist="" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="btnClose" ActionTag="-547653348" Tag="1003" IconVisible="False" LeftMargin="544.0000" RightMargin="34.0000" TopMargin="29.5000" BottomMargin="869.5000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="32" Scale9Height="39" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="62.0000" Y="61.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="575.0000" Y="900.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.8984" Y="0.9375" />
                <PreSize X="0.0969" Y="0.0635" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="Normal" Path="images/skills_panel/button8.png" Plist="" />
                <NormalFileData Type="Normal" Path="images/skills_panel/button8.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btnBase" ActionTag="751796652" Tag="1004" IconVisible="False" LeftMargin="34.5000" RightMargin="464.5000" TopMargin="124.0013" BottomMargin="763.9987" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="111" Scale9Height="50" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="141.0000" Y="72.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="105.0000" Y="799.9987" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.1641" Y="0.8333" />
                <PreSize X="0.2203" Y="0.0750" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="Normal" Path="images/skills_panel/button2.png" Plist="" />
                <NormalFileData Type="Normal" Path="images/skills_panel/button2.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btnSpecial" ActionTag="-214524123" Tag="1005" IconVisible="False" LeftMargin="176.5000" RightMargin="322.5000" TopMargin="124.0013" BottomMargin="763.9987" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="111" Scale9Height="50" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="141.0000" Y="72.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="247.0000" Y="799.9987" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.3859" Y="0.8333" />
                <PreSize X="0.2203" Y="0.0750" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="Normal" Path="images/skills_panel/button4.png" Plist="" />
                <NormalFileData Type="Normal" Path="images/skills_panel/button4.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btnEnergy" ActionTag="1186544771" Tag="1006" IconVisible="False" LeftMargin="318.5000" RightMargin="180.5000" TopMargin="124.0000" BottomMargin="764.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="111" Scale9Height="50" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="141.0000" Y="72.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="389.0000" Y="800.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.6078" Y="0.8333" />
                <PreSize X="0.2203" Y="0.0750" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="Normal" Path="images/skills_panel/button3.png" Plist="" />
                <NormalFileData Type="Normal" Path="images/skills_panel/button3.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btnPassive" ActionTag="-687701146" Tag="1007" IconVisible="False" LeftMargin="460.5000" RightMargin="30.5000" TopMargin="120.0011" BottomMargin="759.9989" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="119" Scale9Height="58" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="149.0000" Y="80.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="535.0000" Y="799.9989" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.8359" Y="0.8333" />
                <PreSize X="0.2328" Y="0.0833" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="Normal" Path="images/skills_panel/button1.png" Plist="" />
                <NormalFileData Type="Normal" Path="images/skills_panel/button1.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="nodeSkillItem0" ActionTag="-952121461" Tag="1008" IconVisible="True" LeftMargin="320.0000" RightMargin="320.0000" TopMargin="277.0000" BottomMargin="683.0000" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="320.0000" Y="683.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.7115" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="modules/main/NodeSkillItem.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="nodeSkillItem1" ActionTag="366764945" Tag="1019" IconVisible="True" LeftMargin="320.0000" RightMargin="320.0000" TopMargin="437.0000" BottomMargin="523.0000" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="320.0000" Y="523.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5448" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="modules/main/NodeSkillItem.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="nodeSkillItem2" ActionTag="-136169577" Tag="1030" IconVisible="True" LeftMargin="320.0000" RightMargin="320.0000" TopMargin="597.0000" BottomMargin="363.0000" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="320.0000" Y="363.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.3781" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="modules/main/NodeSkillItem.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="nodeSkillItem3" ActionTag="1551880615" Tag="1041" IconVisible="True" LeftMargin="320.0007" RightMargin="319.9993" TopMargin="757.0000" BottomMargin="203.0000" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="320.0007" Y="203.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.2115" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="modules/main/NodeSkillItem.csd" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="layoutBtns" ActionTag="-1487796346" Tag="198" IconVisible="False" BottomMargin="823.0000" BackColorAlpha="102" ColorAngle="90.0000" ctype="PanelObjectData">
            <Size X="640.0000" Y="137.0000" />
            <Children>
              <AbstractNodeData Name="spriteBg" ActionTag="596609547" Tag="81" IconVisible="False" TopMargin="-37.0000" ctype="SpriteObjectData">
                <Size X="640.0000" Y="137.0000" />
                <AnchorPoint ScaleY="1.0000" />
                <Position Y="137.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition Y="1.3700" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="images/levels/bottom3.png" Plist="" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="btn0" ActionTag="278364990" UserData="1000" Tag="193" IconVisible="False" LeftMargin="5.0000" RightMargin="537.0000" TopMargin="8.0000" BottomMargin="31.0000" TouchEnable="True" FontSize="30" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="68" Scale9Height="76" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="98.0000" Y="98.0000" />
                <Children>
                  <AbstractNodeData Name="spriteLockState" Visible="False" ActionTag="-1200952394" Tag="90" IconVisible="False" LeftMargin="15.0000" RightMargin="15.0000" TopMargin="38.0000" BottomMargin="38.0000" ctype="SpriteObjectData">
                    <Size X="46.0000" Y="46.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="49.0000" Y="49.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.1063" Y="0.1833" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="54.0000" Y="80.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0844" Y="0.5839" />
                <PreSize X="0.1531" Y="0.7153" />
                <FontResource Type="Normal" Path="fonts/ktjt.ttf" Plist="" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="MarkedSubImage" Path="images/girl/box2.png" Plist="modules/main/PlistMain.plist" />
                <NormalFileData Type="MarkedSubImage" Path="images/girl/box1.png" Plist="modules/main/PlistMain.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btn1" ActionTag="-1524352908" UserData="1001" Tag="198" IconVisible="False" LeftMargin="111.0000" RightMargin="431.0000" TopMargin="8.0000" BottomMargin="31.0000" TouchEnable="True" FontSize="30" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="68" Scale9Height="76" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="98.0000" Y="98.0000" />
                <Children>
                  <AbstractNodeData Name="spriteLockState" Visible="False" ActionTag="-1048350666" Tag="208" IconVisible="False" LeftMargin="15.0000" RightMargin="15.0000" TopMargin="38.0000" BottomMargin="38.0000" ctype="SpriteObjectData">
                    <Size X="46.0000" Y="46.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="49.0000" Y="49.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.1063" Y="0.1833" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="160.0000" Y="80.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.2500" Y="0.5839" />
                <PreSize X="0.1531" Y="0.7153" />
                <FontResource Type="Normal" Path="fonts/ktjt.ttf" Plist="" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="MarkedSubImage" Path="images/girl/box2.png" Plist="modules/main/PlistMain.plist" />
                <NormalFileData Type="MarkedSubImage" Path="images/girl/box1.png" Plist="modules/main/PlistMain.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btn2" ActionTag="940814926" UserData="1002" Tag="200" IconVisible="False" LeftMargin="217.0000" RightMargin="325.0000" TopMargin="8.0000" BottomMargin="31.0000" TouchEnable="True" FontSize="30" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="68" Scale9Height="76" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="98.0000" Y="98.0000" />
                <Children>
                  <AbstractNodeData Name="spriteLockState" Visible="False" ActionTag="-213993256" Tag="209" IconVisible="False" LeftMargin="15.0000" RightMargin="15.0000" TopMargin="38.0000" BottomMargin="38.0000" ctype="SpriteObjectData">
                    <Size X="46.0000" Y="46.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="49.0000" Y="49.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.1063" Y="0.1833" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="266.0000" Y="80.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4156" Y="0.5839" />
                <PreSize X="0.1531" Y="0.7153" />
                <FontResource Type="Normal" Path="fonts/ktjt.ttf" Plist="" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="MarkedSubImage" Path="images/girl/box2.png" Plist="modules/main/PlistMain.plist" />
                <NormalFileData Type="MarkedSubImage" Path="images/girl/box1.png" Plist="modules/main/PlistMain.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btn3" ActionTag="1470003503" UserData="1003" Tag="202" IconVisible="False" LeftMargin="324.0000" RightMargin="218.0000" TopMargin="8.0000" BottomMargin="31.0000" TouchEnable="True" FontSize="30" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="68" Scale9Height="76" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="98.0000" Y="98.0000" />
                <Children>
                  <AbstractNodeData Name="spriteLockState" ActionTag="-139626396" Tag="210" IconVisible="False" LeftMargin="15.0000" RightMargin="15.0000" TopMargin="38.0000" BottomMargin="38.0000" ctype="SpriteObjectData">
                    <Size X="102.0000" Y="57.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="49.0000" Y="49.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.1063" Y="0.1833" />
                    <FileData Type="MarkedSubImage" Path="images/girl/buy.png" Plist="modules/main/PlistMain.plist" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="373.0000" Y="80.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5828" Y="0.5839" />
                <PreSize X="0.1531" Y="0.7153" />
                <FontResource Type="Normal" Path="fonts/ktjt.ttf" Plist="" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="MarkedSubImage" Path="images/girl/box2.png" Plist="modules/main/PlistMain.plist" />
                <NormalFileData Type="MarkedSubImage" Path="images/girl/box1.png" Plist="modules/main/PlistMain.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btn4" ActionTag="-1864829275" UserData="1004" Tag="204" IconVisible="False" LeftMargin="431.0000" RightMargin="111.0000" TopMargin="8.0000" BottomMargin="31.0000" TouchEnable="True" FontSize="30" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="68" Scale9Height="76" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="98.0000" Y="98.0000" />
                <Children>
                  <AbstractNodeData Name="spriteLockState" ActionTag="-2002036731" Tag="211" IconVisible="False" LeftMargin="15.0000" RightMargin="15.0000" TopMargin="38.0000" BottomMargin="38.0000" ctype="SpriteObjectData">
                    <Size X="74.0000" Y="28.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="49.0000" Y="49.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.1063" Y="0.1833" />
                    <FileData Type="MarkedSubImage" Path="images/girl/not_unlock.png" Plist="modules/main/PlistMain.plist" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="480.0000" Y="80.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7500" Y="0.5839" />
                <PreSize X="0.1531" Y="0.7153" />
                <FontResource Type="Normal" Path="fonts/ktjt.ttf" Plist="" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="MarkedSubImage" Path="images/girl/box2.png" Plist="modules/main/PlistMain.plist" />
                <NormalFileData Type="MarkedSubImage" Path="images/girl/box1.png" Plist="modules/main/PlistMain.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btn5" ActionTag="-966584021" UserData="1005" Tag="206" IconVisible="False" LeftMargin="537.0000" RightMargin="5.0000" TopMargin="8.0000" BottomMargin="31.0000" TouchEnable="True" FontSize="30" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="68" Scale9Height="76" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="98.0000" Y="98.0000" />
                <Children>
                  <AbstractNodeData Name="spriteLockState" ActionTag="-1220956690" Tag="212" IconVisible="False" LeftMargin="15.0000" RightMargin="15.0000" TopMargin="38.0000" BottomMargin="38.0000" ctype="SpriteObjectData">
                    <Size X="74.0000" Y="28.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="49.0000" Y="49.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.1063" Y="0.1833" />
                    <FileData Type="MarkedSubImage" Path="images/girl/not_unlock.png" Plist="modules/main/PlistMain.plist" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="586.0000" Y="80.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.9156" Y="0.5839" />
                <PreSize X="0.1531" Y="0.7153" />
                <FontResource Type="Normal" Path="fonts/ktjt.ttf" Plist="" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="MarkedSubImage" Path="images/girl/box2.png" Plist="modules/main/PlistMain.plist" />
                <NormalFileData Type="MarkedSubImage" Path="images/girl/box1.png" Plist="modules/main/PlistMain.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
            <Position X="320.0000" Y="960.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="1.0000" />
            <PreSize X="1.0000" Y="0.1427" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>