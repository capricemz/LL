<GameProjectFile>
  <PropertyGroup Type="Layer" Name="LayerBattle" ID="976fed9b-322a-4f7d-9264-c5be48f5bb0d" Version="2.3.2.3" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="LayerBattle" ctype="GameLayerObjectData">
        <Size X="640.0000" Y="960.0000" />
        <Children>
          <AbstractNodeData Name="Panel" CanEdit="False" ActionTag="1413142824" Tag="95" IconVisible="False" LeftMargin="0.8122" RightMargin="-0.8122" TopMargin="0.8122" BottomMargin="-0.8122" TouchEnable="True" ClipAble="True" BackColorAlpha="102" ColorAngle="90.0000" ctype="PanelObjectData">
            <Size X="640.0000" Y="960.0000" />
            <Children>
              <AbstractNodeData Name="SpriteBg" CanEdit="False" ActionTag="745239092" Tag="105" IconVisible="False" ctype="SpriteObjectData">
                <Size X="640.0000" Y="960.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="320.0000" Y="480.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="images/bg/battle_bg1.png" Plist="" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="pk" CanEdit="False" ActionTag="-1651146651" Tag="516" IconVisible="False" LeftMargin="0.0003" RightMargin="-0.0003" BottomMargin="260.0000" TouchEnable="True" BackColorAlpha="102" ColorAngle="90.0000" ctype="PanelObjectData">
                <Size X="640.0000" Y="700.0000" />
                <Children>
                  <AbstractNodeData Name="monster_role1" ActionTag="1354680425" Tag="519" IconVisible="False" LeftMargin="-525.0000" RightMargin="-235.0000" TopMargin="-775.0000" BottomMargin="275.0000" FlipX="True" ctype="SpriteObjectData">
                    <Size X="1400.0000" Y="1200.0000" />
                    <AnchorPoint ScaleX="0.5000" />
                    <Position X="175.0000" Y="275.0000" />
                    <Scale ScaleX="0.2500" ScaleY="0.2500" />
                    <CColor A="255" R="191" G="191" B="191" />
                    <PrePosition X="0.2734" Y="0.3929" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="images/role_image/role_image_44.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="monster_role2" ActionTag="-1801902325" Tag="520" IconVisible="False" LeftMargin="129.9994" RightMargin="60.0006" TopMargin="-775.0000" BottomMargin="275.0001" FlipX="True" ctype="SpriteObjectData">
                    <Size X="450.0000" Y="1200.0000" />
                    <AnchorPoint ScaleX="0.5000" />
                    <Position X="354.9994" Y="275.0001" />
                    <Scale ScaleX="0.2500" ScaleY="0.2500" />
                    <CColor A="255" R="191" G="191" B="191" />
                    <PrePosition X="0.5547" Y="0.3929" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="images/role_image/role_image_32.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="player_role" ActionTag="-1699534646" Tag="415" IconVisible="True" LeftMargin="512.0000" RightMargin="128.0000" TopMargin="680.0000" BottomMargin="20.0000" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="512.0000" Y="20.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.8000" Y="0.0286" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="modules/battle/ShooterAction.csd" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="monster_role0" ActionTag="-1890571600" Tag="419" IconVisible="True" LeftMargin="128.0000" RightMargin="512.0000" TopMargin="680.0000" BottomMargin="20.0000" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="128.0000" Y="20.0000" />
                    <Scale ScaleX="-1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.2000" Y="0.0286" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="modules/battle/ShooterAction.csd" Plist="" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="0.0003" Y="260.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0000" Y="0.2708" />
                <PreSize X="1.0000" Y="0.7292" />
                <SingleColor A="255" R="150" G="200" B="255" />
                <FirstColor A="255" R="150" G="200" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="player_Panel" CanEdit="False" ActionTag="-26207480" Tag="97" IconVisible="False" TopMargin="658.0000" TouchEnable="True" BackColorAlpha="102" ColorAngle="90.0000" ctype="PanelObjectData">
                <Size X="640.0000" Y="302.0000" />
                <Children>
                  <AbstractNodeData Name="playerBg" CanEdit="False" ActionTag="-1885587179" Tag="98" IconVisible="False" TopMargin="2.0000" BottomMargin="-2.0000" ctype="SpriteObjectData">
                    <Size X="640.0000" Y="302.0000" />
                    <AnchorPoint ScaleX="0.5000" />
                    <Position X="320.0000" Y="-2.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="-0.0066" />
                    <PreSize X="1.0000" Y="1.0000" />
                    <FileData Type="Normal" Path="images/battle1/battle_bg.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="skill_card0" ActionTag="1393516540" Tag="228" IconVisible="True" LeftMargin="44.0000" RightMargin="596.0000" TopMargin="121.0000" BottomMargin="181.0000" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="44.0000" Y="181.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.0688" Y="0.5993" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="modules/main/NodeGrid.csd" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="skill_card1" ActionTag="-458883852" Tag="211" IconVisible="True" LeftMargin="129.0000" RightMargin="511.0000" TopMargin="121.0000" BottomMargin="181.0000" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="129.0000" Y="181.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.2016" Y="0.5993" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="modules/main/NodeGrid.csd" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="skill_card2" ActionTag="2033575454" Tag="194" IconVisible="True" LeftMargin="215.0000" RightMargin="425.0000" TopMargin="121.0000" BottomMargin="181.0000" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="215.0000" Y="181.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.3359" Y="0.5993" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="modules/main/NodeGrid.csd" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="layoutHeadMaid" CanEdit="False" ActionTag="-648104566" Tag="1317" IconVisible="False" HorizontalEdge="RightEdge" VerticalEdge="BottomEdge" LeftMargin="258.0000" TopMargin="57.9993" BottomMargin="0.0007" TouchEnable="True" ClipAble="True" BackColorAlpha="102" ColorAngle="90.0000" ctype="PanelObjectData">
                    <Size X="382.0000" Y="244.0000" />
                    <AnchorPoint ScaleX="1.0000" />
                    <Position X="640.0000" Y="0.0007" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="1.0000" />
                    <PreSize X="0.5969" Y="0.8079" />
                    <SingleColor A="255" R="150" G="200" B="255" />
                    <FirstColor A="255" R="150" G="200" B="255" />
                    <EndColor A="255" R="255" G="255" B="255" />
                    <ColorVector ScaleY="1.0000" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="1.0000" Y="0.3146" />
                <SingleColor A="255" R="150" G="200" B="255" />
                <FirstColor A="255" R="150" G="200" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="monster_Panel" CanEdit="False" ActionTag="1688007759" Tag="114" IconVisible="False" VerticalEdge="TopEdge" LeftMargin="0.0023" RightMargin="-0.0023" TopMargin="-0.0004" BottomMargin="760.0004" TouchEnable="True" BackColorAlpha="102" ColorAngle="90.0000" ctype="PanelObjectData">
                <Size X="640.0000" Y="200.0000" />
                <Children>
                  <AbstractNodeData Name="mst_head_bg" ActionTag="-1619811641" Tag="115" IconVisible="False" RightMargin="536.0000" BottomMargin="96.0000" ctype="SpriteObjectData">
                    <Size X="104.0000" Y="104.0000" />
                    <Children>
                      <AbstractNodeData Name="mst_head" ActionTag="681100803" Tag="123" IconVisible="False" HorizontalEdge="BothEdge" VerticalEdge="BothEdge" LeftMargin="29.0000" RightMargin="29.0000" TopMargin="29.0000" BottomMargin="29.0000" ctype="SpriteObjectData">
                        <Size X="46.0000" Y="46.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="52.0000" Y="52.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.5000" />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                        <BlendFunc Src="770" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="52.0000" Y="148.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.0812" Y="0.7400" />
                    <PreSize X="0.1625" Y="0.5200" />
                    <FileData Type="Normal" Path="images/battle1/mst_head.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="mst_hp" ActionTag="-2098364649" Tag="116" IconVisible="False" LeftMargin="96.0000" RightMargin="216.0000" TopMargin="5.5000" BottomMargin="151.5000" ctype="SpriteObjectData">
                    <Size X="328.0000" Y="43.0000" />
                    <Children>
                      <AbstractNodeData Name="hp_bar" ActionTag="1078131865" Tag="117" IconVisible="False" LeftMargin="9.0000" RightMargin="8.0000" TopMargin="11.0000" BottomMargin="13.0000" ProgressInfo="100" ctype="LoadingBarObjectData">
                        <Size X="311.0000" Y="19.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="164.5000" Y="22.5000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5015" Y="0.5233" />
                        <PreSize X="0.9482" Y="0.4419" />
                        <ImageFileData Type="Normal" Path="images/battle1/mst_hp.png" Plist="" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="hp_txt" ActionTag="1615143708" Tag="118" IconVisible="False" LeftMargin="115.0000" RightMargin="133.0000" TopMargin="6.0000" BottomMargin="13.0000" FontSize="20" LabelText="2000/2000" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="80.0000" Y="24.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="155.0000" Y="25.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.4726" Y="0.5814" />
                        <PreSize X="0.3476" Y="0.5581" />
                        <FontResource Type="Normal" Path="fonts/ktjt.ttf" Plist="" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="260.0000" Y="173.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.4063" Y="0.8650" />
                    <PreSize X="0.5125" Y="0.2150" />
                    <FileData Type="Normal" Path="images/battle1/mst_hp_bg.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="round" ActionTag="1175253367" Tag="119" IconVisible="False" LeftMargin="451.0000" BottomMargin="149.0000" ctype="SpriteObjectData">
                    <Size X="189.0000" Y="51.0000" />
                    <Children>
                      <AbstractNodeData Name="round_txt" ActionTag="-997308081" Tag="120" IconVisible="False" LeftMargin="30.0001" RightMargin="78.9999" TopMargin="12.0006" BottomMargin="14.9994" FontSize="20" LabelText="回合数：" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="80.0000" Y="24.0000" />
                        <AnchorPoint ScaleY="0.5000" />
                        <Position X="30.0001" Y="26.9994" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.1587" Y="0.5294" />
                        <PreSize X="0.6032" Y="0.4706" />
                        <FontResource Type="Normal" Path="fonts/ktjt.ttf" Plist="" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="round_num" ActionTag="884283887" Tag="121" IconVisible="False" LeftMargin="108.3907" RightMargin="36.6093" TopMargin="13.2239" BottomMargin="13.7761" FontSize="20" LabelText="20/20" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="44.0000" Y="24.0000" />
                        <AnchorPoint ScaleY="0.5000" />
                        <Position X="108.3907" Y="25.7761" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5735" Y="0.5054" />
                        <PreSize X="0.6032" Y="0.4706" />
                        <FontResource Type="Normal" Path="fonts/ktjt.ttf" Plist="" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="545.5000" Y="174.5000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.8523" Y="0.8725" />
                    <PreSize X="0.2953" Y="0.2550" />
                    <FileData Type="Normal" Path="images/battle1/round_bg.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="mst_name" ActionTag="163108435" Tag="122" IconVisible="False" LeftMargin="103.5005" RightMargin="433.4995" TopMargin="53.0085" BottomMargin="114.9915" ctype="SpriteObjectData">
                    <Size X="103.0000" Y="32.0000" />
                    <AnchorPoint ScaleY="0.5000" />
                    <Position X="103.5005" Y="130.9915" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.1617" Y="0.6550" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="images/battle1/name.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="mst_card0" ActionTag="991326518" Tag="143" IconVisible="True" LeftMargin="595.0000" RightMargin="45.0000" TopMargin="116.0000" BottomMargin="84.0000" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="595.0000" Y="84.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.9297" Y="0.4200" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="modules/main/NodeGrid.csd" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="mst_card1" ActionTag="-1803716259" Tag="160" IconVisible="True" LeftMargin="509.0000" RightMargin="131.0000" TopMargin="116.0000" BottomMargin="84.0000" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="509.0000" Y="84.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.7953" Y="0.4200" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="modules/main/NodeGrid.csd" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="mst_card2" ActionTag="-512722249" Tag="177" IconVisible="True" LeftMargin="423.0000" RightMargin="217.0000" TopMargin="116.0000" BottomMargin="84.0000" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="423.0000" Y="84.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.6609" Y="0.4200" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="modules/main/NodeGrid.csd" Plist="" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                <Position X="320.0023" Y="960.0004" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="1.0000" />
                <PreSize X="1.0000" Y="0.2083" />
                <SingleColor A="255" R="150" G="200" B="255" />
                <FirstColor A="255" R="150" G="200" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="320.8122" Y="479.1878" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5013" Y="0.4992" />
            <PreSize X="1.0000" Y="1.0000" />
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