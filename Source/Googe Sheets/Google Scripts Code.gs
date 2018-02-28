var device_ID = 'DEVICE_ID_GOES_HERE'; 
var access_token = 'ACCESS_TOKEN_GOES_HERE'; 
var variables = ['temp', 'voltage'];
var checkLatestData = true;
var refreshTime = 300;
var rowChecker = 4289;

//  Select the active spreadsheet
var sheet = SpreadsheetApp.getActiveSheet();

//	Function to create a header
function showHeader()	{
	//	Clear the first row
	sheet.deleteRow(1);

	//	At first add the timestamp
	sheet.getRange(1,1).setValue('Timestamp');

	//	Loop through all the variables and add the names of them
	for (var i = 0; i < variables.length; i++) {
		sheet.getRange(1,2 + i).setValue(variables[i]);
	};


	collectData();
}

//	Function to show the latest data
function showLatestData(timestamp, results)	{
	//	At first add the timestamp
	sheet.getRange(2,3 + variables.length).setValue(timestamp);

	//	Loop through all the variables and add the names of them
	for (var i = 0; i < results.length; i++) {
		sheet.getRange(2,4 + variables.length).setValue(results[i]);
	};
}

//  Function to get and parse the JSON variable from the spark API
function getResponse(variable){
	var JSONResponse = UrlFetchApp.fetch("https://api.spark.io/v1/devices/" + device_ID + "/" + variable + "?access_token=" + access_token);
	
	var response = JSON.parse(JSONResponse.getContentText());
	return response.result;		
}

function collectData()  {
	//	Declare a result array
	var timestamp = Utilities.formatDate(new Date(), "HST", "yyyy-MM-dd HH:mm:ss");
  
	var results = [timestamp];
	var resultsWithKey = [];

	//	Loop through the array with variables and get their content
	for (var i = 0; i < variables.length; i++) {

		//	Push the results in an array
		results.push(getResponse(variables[i]));
		resultsWithKey[variables[i]] = getResponse(variables[i]);
	};

	if(checkLatestData) showLatestData(timestamp, results)
	
    //  Add the responses to the spreadsheet
	sheet.appendRow(results);
    //addRows();

}
function createSheet(){
var ss = SpreadsheetApp.getActiveSpreadsheet();
 var sheet = ss.getSheets()[0];

 var chart = sheet.newChart()
     .setChartType(Charts.ChartType.LINE)
     .addRange(sheet.getRange("B3:C620"))
     .setPosition(10, 10, 8, 8)
     .build();
  
    
  
 sheet.insertChart(chart);
}
function clearRange() {
  //replace 'Sheet1' with your actual sheet name
  var csheet = SpreadsheetApp.getActiveSpreadsheet();
  var ccsheet = csheet.getSheets()[0];
  ccsheet.getRange('A2:G2000').clearContent();
}

/*function addRows(){
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var cell = ss.getCell(rowChecker, 1);
  if(!cell.isBlank()){
  for(var i = 0; i < 1000; i++){
    var sheet = SpreadsheetApp.getActiveSheet();
    sheet.insertRowAfter(rowChecker);
    rowChecker++;
  }
  }
}*/