// Modules to control application life and create native browser window
const {app, BrowserWindow, ipcMain} = require('electron')
const path = require('path')

function createWindow () {
  // Create the browser window.
  const mainWindow = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      preload: path.join(__dirname, 'preload.js')
    }
  });

  // and load the index.html of the app.
  mainWindow.loadFile('index.html')

  // Open the DevTools.
  // mainWindow.webContents.openDevTools()
}

app.whenReady().then(() => {
  createWindow();    

  ipcMain.on('add_data', (event, data) => {
    // console.log in main process will print to the terminal console NOT from dev tools as renderer process logging
    // log the add data numbers in the terminal console, so that dll cpp can parse it in that format to get them
    console.log("add_data=", data);

    // close electron app to continue in the dll_cpp flow and get the frontend data from the console logging
    app.quit();
  });
})

app.on('window-all-closed', function () {
  if (process.platform !== 'darwin') app.quit()
})

