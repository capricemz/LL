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
            <FileData Type="Normal" Path="images/bg/gril_bg.png" Plist="" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="layoutMaid" ActionTag="-1782727080" CallBackType="Click" Tag="52" IconVisible="False" ClipAble="True" BackColorAlpha="0" ColorAngle="90.0000" ctype="PanelObjectData">
            <Size X="640.0000" Y="960.0000" />
            <Children>
              <AbstractNodeData Name="role_icon" ActionTag="1293731001" Tag="106" IconVisible="False" LeftMargin="-30.0000" RightMargin="-30.0000" TopMargin="20.0000" BottomMargin="-260.0000" ctype="SpriteObjectData">
                <Size X="700.0000" Y="1200.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="320.0000" Y="340.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.3542" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="images/role_image/role_image_52.png" Plist="" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="spriteBuyTip" ActionTag="1310964043" Tag="54" IconVisible="False" LeftMargin="239.5001" RightMargin="239.4999" TopMargin="473.4973" BottomMargin="433.5027" ctype="SpriteObjectData">
                <Size X="161.0000" Y="53.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="320.0001" Y="460.0027" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.4792" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="MarkedSubImage" Path="images/girl/buy1.png" Plist="modules/main/PlistMain.plist" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="spriteNameBg" ActionTag="1881748643" Tag="57" IconVisible="False" LeftMargin="196.5002" RightMargin="196.4998" TopMargin="750.5000" BottomMargin="154.5000" ctype="SpriteObjectData">
                <Size X="247.0000" Y="55.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="320.0002" Y="182.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.1896" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="MarkedSubImage" Path="images/girl/role_name.png" Plist="modules/main/PlistMain.plist" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="btnPrev" ActionTag="-1233900949" Tag="213" IconVisible="False" HorizontalEdge="LeftEdge" LeftMargin="20.0000" RightMargin="512.4971" TopMargin="564.5011" BottomMargin="316.4989" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="77" Scale9Height="57" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="107.0000" Y="79.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="73.5000" Y="355.9989" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.1156" Y="0.3708" />
                <PreSize X="0.1672" Y="0.0823" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="MarkedSubImage" Path="images/girl/left.png" Plist="modules/main/PlistMain.plist" />
                <NormalFileData Type="MarkedSubImage" Path="images/girl/left.png" Plist="modules/main/PlistMain.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btnNext" ActionTag="-1243916847" Tag="214" IconVisible="False" HorizontalEdge="RightEdge" LeftMargin="430.0001" RightMargin="20.0000" TopMargin="558.0011" BottomMargin="309.9989" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="90" Scale9Height="70" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="120.0000" Y="92.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="560.0000" Y="355.9989" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7656" Y="0.3708" />
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
          <AbstractNodeData Name="layoutSkillItems" ActionTag="-573801320" VisibleForFrame="False" Tag="998" IconVisible="False" LeftMargin="0.0001" RightMargin="-0.0001" ClipAble="True" BackColorAlpha="0" ColorAngle="90.0000" ctype="PanelObjectData">
            <Size X="640.0000" Y="960.0000" />
            <Children>
              <AbstractNodeData Name="spriteBg" ActionTag="32141392" Tag="999" IconVisible="False" LeftMargin="-18.5018" RightMargin="-18.4982" TopMargin="-11.9965" BottomMargin="31.9965" ctype="SpriteObjectData">
                <Size X="677.0000" Y="940.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="319.9982" Y="501.9965" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5229" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="images/skills_panel/bg2.png" Plist="" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="spriteIcon" ActionTag="1909835061" Tag="1000" IconVisible="False" LeftMargin="34.9996" RightMargin="515.0004" TopMargin="59.0055" BottomMargin="810.9945" ctype="SpriteObjectData">
                <Size X="90.0000" Y="90.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="79.9996" Y="855.9945" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.1250" Y="0.8917" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="images/skills_panel/zhiye.png" Plist="" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="spriteName" ActionTag="1127073709" Tag="1001" IconVisible="False" LeftMargin="137.9996" RightMargin="346.0004" TopMargin="70.0052" BottomMargin="821.9948" ctype="SpriteObjectData">
                <Size X="156.0000" Y="68.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="215.9996" Y="855.9948" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.3375" Y="0.8917" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="images/skills_panel/name button.png" Plist="" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="spriteSkillDesc" ActionTag="1389928227" Tag="1002" IconVisible="False" LeftMargin="312.4994" RightMargin="104.5006" TopMargin="69.0055" BottomMargin="832.9945" ctype="SpriteObjectData">
                <Size X="223.0000" Y="58.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="423.9994" Y="861.9945" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.6625" Y="0.8979" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="images/skills_panel/Skills button.png" Plist="" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="btnClose" ActionTag="-547653348" Tag="1003" IconVisible="False" LeftMargin="543.9999" RightMargin="34.0001" TopMargin="53.5068" BottomMargin="845.4932" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="32" Scale9Height="39" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="62.0000" Y="61.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="574.9999" Y="875.9932" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.8984" Y="0.9125" />
                <PreSize X="0.0969" Y="0.0635" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="Normal" Path="images/skills_panel/button8.png" Plist="" />
                <NormalFileData Type="Normal" Path="images/skills_panel/button8.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btnBase" ActionTag="751796652" Tag="1004" IconVisible="False" LeftMargin="34.4990" RightMargin="464.5010" TopMargin="148.0059" BottomMargin="739.9941" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="111" Scale9Height="50" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="141.0000" Y="72.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="104.9990" Y="775.9941" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.1641" Y="0.8083" />
                <PreSize X="0.2203" Y="0.0750" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="Normal" Path="images/skills_panel/button2.png" Plist="" />
                <NormalFileData Type="Normal" Path="images/skills_panel/button2.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btnSpecial" ActionTag="-214524123" Tag="1005" IconVisible="False" LeftMargin="176.4974" RightMargin="322.5026" TopMargin="148.0059" BottomMargin="739.9941" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="111" Scale9Height="50" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="141.0000" Y="72.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="246.9974" Y="775.9941" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.3859" Y="0.8083" />
                <PreSize X="0.2203" Y="0.0750" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="Normal" Path="images/skills_panel/button4.png" Plist="" />
                <NormalFileData Type="Normal" Path="images/skills_panel/button4.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btnEnergy" ActionTag="1186544771" Tag="1006" IconVisible="False" LeftMargin="318.4973" RightMargin="180.5027" TopMargin="148.0052" BottomMargin="739.9948" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="111" Scale9Height="50" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="141.0000" Y="72.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="388.9973" Y="775.9948" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.6078" Y="0.8083" />
                <PreSize X="0.2203" Y="0.0750" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="Normal" Path="images/skills_panel/button3.png" Plist="" />
                <NormalFileData Type="Normal" Path="images/skills_panel/button3.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btnPassive" ActionTag="-687701146" Tag="1007" IconVisible="False" LeftMargin="460.4972" RightMargin="30.5028" TopMargin="144.0059" BottomMargin="735.9941" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="119" Scale9Height="58" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="149.0000" Y="80.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="534.9972" Y="775.9941" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.8359" Y="0.8083" />
                <PreSize X="0.2328" Y="0.0833" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="Normal" Path="images/skills_panel/button1.png" Plist="" />
                <NormalFileData Type="Normal" Path="images/skills_panel/button1.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="nodeSkillItem0" ActionTag="-952121461" Tag="1008" IconVisible="True" LeftMargin="319.9995" RightMargin="320.0005" TopMargin="301.0038" BottomMargin="658.9962" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="319.9995" Y="658.9962" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.6865" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="modules/main/NodeSkillItem.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="nodeSkillItem1" ActionTag="366764945" Tag="1019" IconVisible="True" LeftMargin="319.9995" RightMargin="320.0005" TopMargin="461.0034" BottomMargin="498.9966" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="319.9995" Y="498.9966" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5198" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="modules/main/NodeSkillItem.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="nodeSkillItem2" ActionTag="-136169577" Tag="1030" IconVisible="True" LeftMargin="319.9995" RightMargin="320.0005" TopMargin="621.0024" BottomMargin="338.9976" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="319.9995" Y="338.9976" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.3531" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="modules/main/NodeSkillItem.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="nodeSkillItem3" ActionTag="1551880615" Tag="1041" IconVisible="True" LeftMargin="320.0006" RightMargin="319.9994" TopMargin="781.0021" BottomMargin="178.9979" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="320.0006" Y="178.9979" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.1865" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="modules/main/NodeSkillItem.csd" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="0.0001" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0000" />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="layoutBtns" ActionTag="-1487796346" Tag="198" IconVisible="False" BottomMargin="810.0000" ClipAble="True" BackColorAlpha="102" ColorAngle="90.0000" ctype="PanelObjectData">
            <Size X="640.0000" Y="150.0000" />
            <Children>
              <AbstractNodeData Name="btn0" ActionTag="278364990" UserData="1000" Tag="193" IconVisible="False" VerticalEdge="TopEdge" LeftMargin="8.5001" RightMargin="538.4999" TopMargin="0.0002" BottomMargin="7.9998" TouchEnable="True" FontSize="30" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="93.0000" Y="142.0000" />
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
                  <AbstractNodeData Name="top" CanEdit="False" ActionTag="1133461565" Tag="1301" IconVisible="False" HorizontalEdge="BothEdge" VerticalEdge="BothEdge" LeftMargin="-0.5000" RightMargin="-0.5000" TopMargin="-25.0000" BottomMargin="-25.0000" ctype="SpriteObjectData">
                    <Size X="99.0000" Y="148.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="46.5000" Y="71.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="images/girl/role_head_box.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="55.0001" Y="78.9998" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0859" Y="0.5267" />
                <PreSize X="0.1453" Y="0.9467" />
                <FontResource Type="Normal" Path="fonts/ktjt.ttf" Plist="" />
                <TextColor A="255" R="65" G="65" B="70" />
                <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btn1" ActionTag="-1524352908" UserData="1001" Tag="198" IconVisible="False" VerticalEdge="TopEdge" LeftMargin="114.7000" RightMargin="432.3000" BottomMargin="8.0000" TouchEnable="True" FontSize="30" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="93.0000" Y="142.0000" />
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
                  <AbstractNodeData Name="top" ActionTag="1995192479" Tag="1302" IconVisible="False" HorizontalEdge="BothEdge" VerticalEdge="BothEdge" LeftMargin="-3.0000" RightMargin="-3.0000" TopMargin="-3.0000" BottomMargin="-3.0000" ctype="SpriteObjectData">
                    <Size X="99.0000" Y="148.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="46.5000" Y="71.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="images/girl/role_head_box.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="161.2000" Y="79.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.2519" Y="0.5267" />
                <PreSize X="0.1453" Y="0.9467" />
                <FontResource Type="Normal" Path="fonts/ktjt.ttf" Plist="" />
                <TextColor A="255" R="65" G="65" B="70" />
                <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btn2" ActionTag="940814926" UserData="1002" Tag="200" IconVisible="False" VerticalEdge="TopEdge" LeftMargin="220.9000" RightMargin="326.1000" BottomMargin="8.0000" TouchEnable="True" FontSize="30" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="93.0000" Y="142.0000" />
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
                  <AbstractNodeData Name="top" ActionTag="1186748334" Tag="1303" IconVisible="False" HorizontalEdge="BothEdge" VerticalEdge="BothEdge" LeftMargin="-3.0000" RightMargin="-3.0000" TopMargin="-3.0000" BottomMargin="-3.0000" ctype="SpriteObjectData">
                    <Size X="99.0000" Y="148.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="46.5000" Y="71.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="images/girl/role_head_box.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="267.4000" Y="79.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4178" Y="0.5267" />
                <PreSize X="0.1453" Y="0.9467" />
                <FontResource Type="Normal" Path="fonts/ktjt.ttf" Plist="" />
                <TextColor A="255" R="65" G="65" B="70" />
                <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btn3" ActionTag="1470003503" UserData="1003" Tag="202" IconVisible="False" VerticalEdge="TopEdge" LeftMargin="327.1001" RightMargin="219.8999" BottomMargin="8.0000" TouchEnable="True" FontSize="30" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="93.0000" Y="142.0000" />
                <Children>
                  <AbstractNodeData Name="spriteLockState" ActionTag="-139626396" Tag="210" IconVisible="False" LeftMargin="15.0000" RightMargin="15.0000" TopMargin="38.0000" BottomMargin="38.0000" ctype="SpriteObjectData">
                    <Size X="89.0000" Y="53.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="49.0000" Y="49.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.1063" Y="0.1833" />
                    <FileData Type="MarkedSubImage" Path="images/girl/buy.png" Plist="modules/main/PlistMain.plist" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="top" ActionTag="1451785440" Tag="1304" IconVisible="False" HorizontalEdge="BothEdge" VerticalEdge="BothEdge" LeftMargin="-3.0000" RightMargin="-3.0000" TopMargin="-3.0000" BottomMargin="-3.0000" ctype="SpriteObjectData">
                    <Size X="99.0000" Y="148.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="46.5000" Y="71.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="images/girl/role_head_box.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="373.6001" Y="79.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5838" Y="0.5267" />
                <PreSize X="0.1453" Y="0.9467" />
                <FontResource Type="Normal" Path="fonts/ktjt.ttf" Plist="" />
                <TextColor A="255" R="65" G="65" B="70" />
                <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btn4" ActionTag="-1864829275" UserData="1004" Tag="204" IconVisible="False" VerticalEdge="TopEdge" LeftMargin="433.3000" RightMargin="113.7000" BottomMargin="8.0000" TouchEnable="True" FontSize="30" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="93.0000" Y="142.0000" />
                <Children>
                  <AbstractNodeData Name="spriteLockState" ActionTag="-2002036731" Tag="211" IconVisible="False" LeftMargin="15.0000" RightMargin="15.0000" TopMargin="38.0000" BottomMargin="38.0000" ctype="SpriteObjectData">
                    <Size X="60.0000" Y="67.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="49.0000" Y="49.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.1063" Y="0.1833" />
                    <FileData Type="MarkedSubImage" Path="images/girl/not_unlock.png" Plist="modules/main/PlistMain.plist" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="top" ActionTag="-1878240050" Tag="1305" IconVisible="False" HorizontalEdge="BothEdge" VerticalEdge="BothEdge" LeftMargin="-3.0000" RightMargin="-3.0000" TopMargin="-3.0000" BottomMargin="-3.0000" ctype="SpriteObjectData">
                    <Size X="99.0000" Y="148.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="46.5000" Y="71.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="images/girl/role_head_box.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="479.8000" Y="79.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7497" Y="0.5267" />
                <PreSize X="0.1453" Y="0.9467" />
                <FontResource Type="Normal" Path="fonts/ktjt.ttf" Plist="" />
                <TextColor A="255" R="65" G="65" B="70" />
                <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btn5" ActionTag="-966584021" UserData="1005" Tag="206" IconVisible="False" VerticalEdge="TopEdge" LeftMargin="539.5000" RightMargin="7.5000" BottomMargin="8.0000" TouchEnable="True" FontSize="30" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="63" Scale9Height="120" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="93.0000" Y="142.0000" />
                <Children>
                  <AbstractNodeData Name="spriteLockState" ActionTag="-1220956690" Tag="212" IconVisible="False" LeftMargin="15.0000" RightMargin="15.0000" TopMargin="38.0000" BottomMargin="38.0000" ctype="SpriteObjectData">
                    <Size X="60.0000" Y="67.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="49.0000" Y="49.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.1063" Y="0.1833" />
                    <FileData Type="MarkedSubImage" Path="images/girl/not_unlock.png" Plist="modules/main/PlistMain.plist" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Sprite_38" ActionTag="2027049314" Tag="1306" IconVisible="False" HorizontalEdge="BothEdge" VerticalEdge="BothEdge" LeftMargin="-3.0000" RightMargin="-3.0000" TopMargin="-3.0000" BottomMargin="-3.0000" ctype="SpriteObjectData">
                    <Size X="99.0000" Y="148.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="46.5000" Y="71.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="images/girl/role_head_box.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="586.0000" Y="79.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.9156" Y="0.5267" />
                <PreSize X="0.1453" Y="0.9467" />
                <FontResource Type="Normal" Path="fonts/ktjt.ttf" Plist="" />
                <TextColor A="255" R="65" G="65" B="70" />
                <NormalFileData Type="MarkedSubImage" Path="images/role_head/role_head_bg_6.png" Plist="modules/main/PlistMaidHead1.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
            <Position X="320.0000" Y="960.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="1.0000" />
            <PreSize X="1.0000" Y="0.1563" />
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