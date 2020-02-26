const char MAIN_page[] PROGMEM = R"=====(
<HTML>
	<HEAD>
			<TITLE>My first web page</TITLE>
	</HEAD>
<BODY>
	<form method='post' enctype='application/x-www-form-urlencoded' action='postform/'>
        <input type='text' name='SSID' >
        <input type='text' name='Key' >
        <input type='submit' value='Submit'>
    </form>	
</BODY>
</HTML>
)=====";