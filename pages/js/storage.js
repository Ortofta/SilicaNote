//storage.js
// First, let's create a short helper function to get the database connection
function getDatabase() {
     return openDatabaseSync("SilicaNote", "1.0", "NoteStorageDatabase", 100000);
}

// At the start of the application, we can initialize the tables we need if they haven't been created yet
function initialize() {
    var db = getDatabase();
    db.transaction(
        function(tx) {
            // Create the settings table if it doesn't already exist
            // If the table exists, this is skipped
            tx.executeSql('CREATE TABLE IF NOT EXISTS notes(id INT UNIQUE, note TEXT)');
      });
}

// This function is used to write a setting into the database
function setSetting(id, text) {
   // setting: string representing the setting name (eg: “username”)
   // value: string representing the value of the setting (eg: “myUsername”)
   var db = getDatabase();
   var res = "";
   db.transaction(function(tx) {
        var rs = tx.executeSql('INSERT OR REPLACE INTO notes VALUES (?,?);', [id,text]);
              //console.log(rs.rowsAffected)
              if (rs.rowsAffected > 0) {
                res = "OK";
              } else {
                res = "Error";
              }
        }
  );
  // The function returns “OK” if it was successful, or “Error” if it wasn't
  return res;
}
// This function is used to retrieve a setting from the database
function getSetting(id) {
   var db = getDatabase();
   var res="";
   db.transaction(function(tx) {
     var rs = tx.executeSql('SELECT value FROM notes WHERE id=?;', [id]);
     if (rs.rows.length > 0) {
          res = rs.rows.item(0).text;
     }
  });
  // The function returns “Unknown” if the setting was not found in the database
  // For more advanced projects, this should probably be handled through error codes
  return res;
}

// Get all notes from the database
function getNotes() {
    var db = getDatabase();
    var res = [];
    db.transaction(function(tx) {
        var res = tx.executeSql('SELECT * FROM notes');
    });

    return res;
}
