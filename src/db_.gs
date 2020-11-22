function doGet(e) { 
  
  Logger.log( JSON.stringify(e) );  // view parameters
  
  var result = 'Ok'; // assume success
  
  if (e.parameter == 'null') {
    result = 'No Parameters';
  }
  else {
    var sheet_id = 'AKfycbxr2z__0kjNbziMTFsTEeX_qn1OHuzZcnriaXQu1RGMl7uHndTc'; 		// Spreadsheet ID
    var sheet = SpreadsheetApp.openById(sheet_id).getActiveSheet();		// get Active sheet
    var newRow = sheet.getLastRow() + 1;						
    var rowData = [];
    rowData[0] = new Date(); 											// Timestamp in column A
            
      }
    
   
Logger.log(JSON.stringify(rowData));
    // Write new row below
    var newRange = sheet.getRange(newRow, 1, 1, rowData.length);
    newRange.setValues([rowData]);

  // Return result of operation
//return ContentService.createTextOutput(result);
}
/**
* Remove leading and trailing single or double quotes
*/
function stripQuotes( value ) {
  return value.replace(/^["']|['"]$/g, "");
}

