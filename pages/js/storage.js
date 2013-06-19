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
            tx.executeSql('CREATE TABLE IF NOT EXISTS notes(id INT UNIQUE, title TEXT, note TEXT)');
      });
}

function writeNote(title, text) {
   var db = getDatabase();
   var res = "";
   db.transaction(function(tx) {
        var rs = tx.executeSql('INSERT OR REPLACE INTO notes VALUES (?,?);', [title, text]);
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
function getNote(id) {
   var db = getDatabase();
   var res={};
   db.transaction(function(tx) {
     var rs = tx.executeSql('SELECT value FROM notes WHERE id=?;', [id]);
     if (rs.rows.length > 0) {
         res['note'] = rs.rows.item(0).note;
         res['title'] = rs.rows.item(0).title;
     }
  });

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
