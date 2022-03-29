#include "webHandler.h"

ESP8266WebServer server(80);
String chart;
String p1name = "P1";
String p2name = "P2";
String p3name = "P3";
String valuesP1 = "";
String valuesP2 = "";
String valuesP3 = "";
int plant1stat = 2;
int plant2stat = 2;
int plant3stat = 2;
int plant1rate = 6;
int plant2rate = 6;
int plant3rate = 6;

void createRoot()
{
	chart = "";
	chart += "<html>\n";
	chart += "<head>\n";
	chart += "<script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script>\n";
	chart += "<script type=\"text/javascript\">\n";
	chart += "google.charts.load('current', {'packages':['corechart']});\n";
	chart += "google.charts.setOnLoadCallback(drawChart);\n";
	chart += "\n";
	chart += "function drawChart() {\n";

    //DATA
	chart += "var data1 = google.visualization.arrayToDataTable([\n";
	chart += "['Time', 'Humidity'],\n";
	chart += valuesP1;
	chart += "]);\n";
	chart += "\n";

    chart += "var data2 = google.visualization.arrayToDataTable([\n";
	chart += "['Time', 'Humidity'],\n";
	chart += valuesP2;
	chart += "]);\n";
	chart += "\n";

    chart += "var data3 = google.visualization.arrayToDataTable([\n";
	chart += "['Time', 'Humidity'],\n";
	chart += valuesP3;
	chart += "]);\n";
	chart += "\n";

	chart += "var options = {\n";
	chart += "title: 'Humidity',\n";
	chart += "curveType: 'function',\n";
	chart += "legend: { position: 'bottom' },";
    chart += "legend: 'none',";
    chart += "hAxis: {title: 'Time'},";
    chart += "vAxis: {title: 'Humidity', viewWindow:{min:0,max:100}},";
	chart += "};\n";
	chart += "\n";

	chart += "var chart1 = new google.visualization.LineChart(document.getElementById('curve_chart1'));\n";
    chart += "var chart2 = new google.visualization.LineChart(document.getElementById('curve_chart2'));\n";
    chart += "var chart3 = new google.visualization.LineChart(document.getElementById('curve_chart3'));\n";
	chart += "\n";
	chart += "chart1.draw(data1, options);\n";
    chart += "chart2.draw(data2, options);\n";
    chart += "chart3.draw(data3, options);\n";
	chart += "}\n";
	chart += "</script>\n";
	chart += "<meta http-equiv=\"refresh\" content=\"10\">\n";
	chart += "</head>";
	chart += "<body style=\"background-color: #ffffff; font-family:sans-serif;\">\n";

	chart += "<div>\n";
	chart += "<div style=\"position: absolute; top:0; left:0;  ;width: 100%; background-color: #c9ffb0; border-bottom: forestgreen solid; \">\n";
	chart += "<div style=\"float: left\">\n";
	chart += "<img src=\"https://i.imgur.com/vlhTvL1.png\" height=\"50px\">\n";
	chart += "</div>\n";
	chart += "<h1 style\"margin: 10px;\">Automated Watering System</h1>\n";
	chart += "</div>\n";


	if(waterempty == 1)
	{
		chart += "<div style=\"float: left\">\n";
		chart += "<h1 style=\"color:red;font-size:100px;\"> Watercontainer is empty!</h1>\n";
		chart += "<p>Please fill water into the container and press \"Water now\" on one plant</p>\n";
		chart += "</div>\n";
		chart += "div style=\"width: 100%;overflow: hidden; position: absolute; top: 400px\">\n";
	}
	else
	{
		chart += "<div style=\"width: 100%;overflow: hidden; position: absolute; top: 100px\">\n";
	}


    //PLANT1
    chart += "<div style=\"float: left; border: rgb(0, 194, 58) 2px solid; border-radius:  20px;text-align:center;\">\n";	chart += "<h1>";
	chart += p1name;
	chart += "</h1>\n";
	chart += "<div id=\"curve_chart1\" style=\"width: 450px; height: 250px\"></div>";
	chart += "<form method=\"POST\" >\n";
	switch (plant1stat)
	{
	case 0:
		chart += "Current Setting: No Water<br>";
		break;
	case 1:
		chart += "Current Setting: Low<br>";
		break;
	case 2:
		chart += "Current Setting: Medium<br>";
		break;
	case 3:
		chart += "Current Setting: High<br>";
	default:
		break;
	}
	chart += "Set amount:\n";
	chart += "<select name=\"amount1\">\n";
	chart += "<option value=\"now\">Water Now</option>\n";
	chart += "<option value=\"none\">None</option>\n";
	chart += "<option value=\"low\">Less</option>\n";
	chart += "<option value=\"medium\">Medium</option>\n";
	chart += "<option value=\"high\">Much </option>\n";
	chart += "</select>\n";
	chart += "<input type=\"submit\" value=\"Submit\">\n";
	chart += "</form>\n";
	chart += "<form method=\"POST\" >\n";
	switch (plant1rate)
	{
	case 6:
		chart += "Current Setting: 1 day<br>";
		break;
	case 7:
		chart += "Current Setting: 3 days<br>";
		break;
	case 8:
		chart += "Current Setting: 7 days<br>";
		break;
	case 9:
		chart += "Current Setting: 10 days<br>";
	default:
		break;
	}
	chart += "Set rate:\n";
	chart += "<select name=\"amount1\">\n";
	chart += "<option value=\"6\">1 Day</option>\n";
	chart += "<option value=\"7\">3 Days</option>\n";
	chart += "<option value=\"8\">7 Days</option>\n";
	chart += "<option value=\"9\">10 Days</option>\n";
	chart += "</select>\n";
	chart += "<input type=\"submit\" value=\"Submit\">\n";
	chart += "</form>\n";
	chart += "<form method=\"POST\">\n";
	chart += "<input type=\"text\" name=\"newname1\" placeholder=\"Change Name...\">\n";
	chart += "<input type=\"submit\" value=\"Confirm\">\n";
	chart += "</form>";
	chart += "\n";
	chart += "</div>\n";


    //PLANT2
    chart += "<div style=\"float: left; border: rgb(0, 194, 58) 2px solid; border-radius:  20px;text-align:center;\">\n";
	chart += "<h1>";
	chart += p2name;
	chart += "</h1>\n";
    chart += "<div id=\"curve_chart2\" style=\"width: 450px; height: 250px\"></div>";
	chart += "<form method=\"POST\" >\n";
	switch (plant2stat)
	{
	case 0:
		chart += "Current Setting: No Water<br>";
		break;
	case 1:
		chart += "Current Setting: Low<br>";
		break;
	case 2:
		chart += "Current Setting: Medium<br>";
		break;
	case 3:
		chart += "Current Setting: High<br>";
	default:
		break;
	}
	chart += "Set amount:\n";
	chart += "<select name=\"amount2\">\n";
	chart += "<option value=\"now\">Water Now</option>\n";
	chart += "<option value=\"none\">None</option>\n";
	chart += "<option value=\"low\">Less</option>\n";
	chart += "<option value=\"medium\">Medium</option>\n";
	chart += "<option value=\"high\">Much </option>\n";
	chart += "</select>\n";
	chart += "<input type=\"submit\" value=\"Submit\">\n";
	chart += "</form>\n";
	chart += "<form method=\"POST\" >\n";
	switch (plant2rate)
	{
	case 6:
		chart += "Current Setting: 1 day<br>";
		break;
	case 7:
		chart += "Current Setting: 3 days<br>";
		break;
	case 8:
		chart += "Current Setting: 7 days<br>";
		break;
	case 9:
		chart += "Current Setting: 10 days<br>";
	default:
		break;
	}
	chart += "Set rate:\n";
	chart += "<select name=\"amount1\">\n";
	chart += "<option value=\"6\">1 Day</option>\n";
	chart += "<option value=\"7\">3 Days</option>\n";
	chart += "<option value=\"8\">7 Days</option>\n";
	chart += "<option value=\"9\">10 Days</option>\n";
	chart += "</select>\n";
	chart += "<input type=\"submit\" value=\"Submit\">\n";
	chart += "</form>\n";
	chart += "<form method=\"POST\">\n";
	chart += "<input type=\"text\" name=\"newname2\" placeholder=\"Change Name...\">\n";
	chart += "<input type=\"submit\" value=\"Confirm\">\n";
	chart += "</form>";
	chart += "\n";
	chart += "</div>\n";




    //PLANT3
    chart += "<div style=\"float: left; border: rgb(0, 194, 58) 2px solid; border-radius:  20px;text-align:center;\">\n";
    chart += "<h1>";
	chart += p3name;
	chart += "</h1>\n";
    chart += "<div id=\"curve_chart3\" style=\"width: 450px; height: 250px\"></div>";
    chart += "<form method=\"POST\" >\n";
	switch (plant3stat)
	{
	case 0:
		chart += "Current Setting: No Water<br>";
		break;
	case 1:
		chart += "Current Setting: Low<br>";
		break;
	case 2:
		chart += "Current Setting: Medium<br>";
		break;
	case 3:
		chart += "Current Setting: High<br>";
	default:
		break;
	}
	chart += "Set amount:\n";
	chart += "<select name=\"amount3\">\n";
	chart += "<option value=\"now\">Water Now</option>\n";
	chart += "<option value=\"none\">None</option>\n";
	chart += "<option value=\"low\">Less</option>\n";
	chart += "<option value=\"medium\">Medium</option>\n";
	chart += "<option value=\"high\">Much </option>\n";
	chart += "</select>\n";
	chart += "<input type=\"submit\" value=\"Submit\">\n";
	chart += "</form>\n";
	chart += "<form method=\"POST\" >\n";
	switch (plant3rate)
	{
	case 6:
		chart += "Current Setting: 1 day<br>";
		break;
	case 7:
		chart += "Current Setting: 3 days<br>";
		break;
	case 8:
		chart += "Current Setting: 7 days<br>";
		break;
	case 9:
		chart += "Current Setting: 10 days<br>";
	default:
		break;
	}
	chart += "Set rate:\n";
	chart += "<select name=\"amount1\">\n";
	chart += "<option value=\"6\">1 Day</option>\n";
	chart += "<option value=\"7\">3 Days</option>\n";
	chart += "<option value=\"8\">7 Days</option>\n";
	chart += "<option value=\"9\">10 Days</option>\n";
	chart += "</select>\n";
	chart += "<input type=\"submit\" value=\"Submit\">\n";
	chart += "</form>\n";
	chart += "<form method=\"POST\">\n";
	chart += "<input type=\"text\" name=\"newname3\" placeholder=\"Change Name...\">\n";
	chart += "<input type=\"submit\" value=\"Confirm\">\n";
	chart += "</form>";
	chart += "\n";
	chart += "</div>\n";

	chart += "<div style=\"float: left; margin: 50px\">\n";
	chart += "<img src=\"https://i.imgur.com/bqLP3kS.png\" height=\"400px\">\n";
	chart += "</div>\n";
	chart += "</div>\n";
	chart += "</div>\n";

	chart += "</body>";
}

void handleRoot()
{
	int sendData;
	if (server.argName(0) == "newname1")
	{
		p1name = server.arg(0);
	}
	if (server.argName(0) == "newname2")
	{
		p2name = server.arg(0);
	}
	if (server.argName(0) == "newname3")
	{
		p3name = server.arg(0);
	}

	if (server.argName(0) == "amount1")
	{
		if (server.arg(0) == "none")
		{
			plant1stat = 0;
			sendData = 0;
		}
		if (server.arg(0) == "low")
		{
			plant1stat = 1;
			sendData = 1;
		}
		else if (server.arg(0) == "medium")
		{
			plant1stat = 2;
			sendData = 2;
		}
		else if (server.arg(0) == "high")
		{
			plant1stat = 3;
			sendData = 3;
		}
		else if (server.arg(0) == "now")
		{
			sendData = 5;
		}
		else
		{
			sendData = server.arg(0).toInt();
			plant1rate = sendData;
		}
		sendMessage("Plant1",sendData);

	}
	if (server.argName(0) == "amount2")
	{
		if (server.arg(0) == "none")
		{
			plant2stat = 0;
			sendData = 0;
		}
		if (server.arg(0) == "low")
		{
			plant2stat = 1;
			sendData = 1;
		}
		else if (server.arg(0) == "medium")
		{
			plant2stat = 2;
			sendData = 2;
		}
		else if (server.arg(0) == "high")
		{
			plant2stat = 3;
			sendData = 3;
		}
		else if (server.arg(0) == "now")
		{
			sendData = 5;
		}
		else
		{
			sendData = server.arg(0).toInt();
			plant2rate = sendData;
		}
		sendMessage("Plant2",sendData);
	}
    if (server.argName(0) == "amount3")
	{
		if (server.arg(0) == "none")
		{
			plant3stat = 0;
			sendData = 0;
		}
		if (server.arg(0) == "low")
		{
			plant3stat = 1;
			sendData = 1;
		}
		else if (server.arg(0) == "medium")
		{
			plant3stat = 2;
			sendData = 2;
		}
		else if (server.arg(0) == "high")
		{
			plant3stat = 3;
			sendData = 3;
		}
		else if (server.arg(0) == "now")
		{
			sendData = 5;
		}
		else
		{
			sendData = server.arg(0).toInt();
			plant3rate = sendData;
		}
		sendMessage("Plant3",sendData);
	}
	createRoot();
	server.send(200, "text/html", chart);
}

void handleNotFound()
{
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += (server.method() == HTTP_GET) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";
	for (uint8_t i = 0; i < server.args(); i++)
	{
		message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
	}
	server.send(404, "text/plain", message);
}
