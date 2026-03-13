import SwiftUI

@main
struct PhotoWizardApp: App {
    var body: some Scene {
        WindowGroup {
            ContentView()
            // Setting maximum dimensions based on the full width and full height of the macbook pro 14 inch display resolution
                .frame(minWidth: 600, maxWidth: .infinity, minHeight: 600, maxHeight: .infinity)
        }
        
    }
}
