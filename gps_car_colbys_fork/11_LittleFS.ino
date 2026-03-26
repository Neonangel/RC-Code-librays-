// ************************   LITTLEFS FUNCTIONS   ************************//

// This file contains the functions that are used for the LittleFS for storing misc data that we need for each car.
// The data will be saved in text files. For now, just the variable compass_calibration

// Returns data as a String, this makes it easy to manipulate
String FS_readData(const char * path) {
  Serial.print(path);
  double val = 0.0;
  FILE *file = fopen(path, "r");


  // Testing if file exists
  if (file) {
    Serial.println("Open ok!");
  } else {
    Serial.println("Open failed");
    return "blank";
  }  


  char c;
  String tempString;

  // Loops reads characters and then ends when file is stopped.
  while (true) {
    c = fgetc(file);

    if ( feof(file) ) {
      break;
    } else {
      // Im reading online that using Strings like this can cause memory fragmentation issues. Im gonna change it later
      tempString.concat(c);
    }
  }
  fclose(file);
  return tempString;
}


// Writes data into a path. You need to give the path along with the data and sizeof(data), (MBED_LITTLEFS_FILE_PREFIX path, data, sizeof(data))
// 
void FS_writeData(const char * path, const char * n, size_t nSize) { 
  Serial.print("Writing file: ");
  Serial.println(path);

  // Code was getting stuck here, turns out I forgot to mount the FS using myFS = new LittleFS_MBED();

  FILE *file = fopen(path, "w");

  if (file) {
    Serial.println("File opened");
  } else {
    Serial.println("File failed to open");
    return;
  }

  if (fwrite( (uint8_t *) n, 1, nSize, file )) {
    Serial.println("Writing OK");
  } else {
    Serial.println("Writing failed");
  }


  fclose(file);

}