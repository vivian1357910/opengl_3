# opengl_3
機器手臂

作業環境：Windows10 64bit

編輯器：Visual Studio 2019

語言：C++

套件：OpenGL、Freeglut(引用自NuGet nupengl.core)


作業要求：

1.建立一個3D場景：

	-建立一個平面，將機械手臂和鴨子放在上面。
  
	-調整固定視角，可以方便看到平面上放的物體。
  
	-平面的顏色為深綠色的地面。
  

2.製作3D機械手臂：

	a.機械手臂的構造包含：底座、上臂、前臂、夾子(手)，顏色為白色。
  
	b.利用鍵盤控制機械手臂，包含：底座旋轉、手臂關節角度、手腕旋轉、夾子開關。
  
	c.機械手臂的底座需要像夾娃娃機一樣，可以自由在平面上移動位置。
  
	d.利用鍵盤，按啟動按鍵(例：P鍵)以後，啟動機械手臂"自動追蹤滑鼠"的功能，此時滑鼠點擊畫面中的任意位置，
  
	  機械手臂可以盡最大的可能，往滑鼠的點擊位置伸過去，並做出抓取(夾一下)的動作。
    

3.放置3D黃色小鴨：

	-load小鴨模組繪製黃色小鴨
  

4.場景光源設定，至少兩個光源(場景定點光源、可調控的聚光燈)：

	a.環境光：場景定點光源，固定對整個場景打光。
  
	b.可調控的聚光燈：初始位置，從機械手臂的正上方往下照。
  
	c.利用鍵盤，可以控制光源的顏色(紅、藍、綠等)及方向(類似手電筒)。
  

5.按鍵功能的配置：

	-ESC：關閉視窗
  
	-W、A、S、D：控制機械手臂在平面上的移動
  
	-Z：調整機械手臂"上臂"旋轉角度---沿Y軸逆時針轉30度
  
	-X：調整機械手臂"前臂"旋轉角度---沿X軸逆時針轉30度
  
	-C：調整機械手臂"前臂"旋轉角度---沿Y軸逆時針轉30度
  
	-V：調整機械手臂"前臂"旋轉角度---沿Z軸逆時針轉30度
  
	-F：開關夾子---------------------夾子夾一下
  
	-G：改變聚光燈顏色(預設紫光，每按一次，依序變紅、藍、綠、紫)
  
	-P：開關機械手臂自動抓取功能
  
	-L：開關聚光燈
  

Bonus：

	1.可開關聚光燈
  
	2.聚光燈隨機械手臂移動，維持在正上方
  
	3.可控制聚光燈顏色
  
	4.鴨子隨機械手臂移動，以其為中心不斷旋轉
  
