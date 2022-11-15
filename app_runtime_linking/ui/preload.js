// To send messages to the listener created above, you can use the ipcRenderer.send API. By default, the renderer process has no Node.js or Electron module access. As an app developer, you need to choose which APIs to expose from your preload script using the contextBridge API.
// In your preload script, add the following code, which will expose a global window.electronAPI variable to your renderer process

const { contextBridge, ipcRenderer } = require('electron')

contextBridge.exposeInMainWorld('electronAPI', {
    sendAddData: (data) => {
        ipcRenderer.send('add_data', data);
    }
})
