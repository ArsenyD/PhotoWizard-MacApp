import SwiftUI

struct ContentView: View {
    @State private var viewModel = ViewModel()
    @State private var isDropAreaTargeted = false
    
    var body: some View {
        if let _ = viewModel.modifiedImageData {
            ImageEditorView()
                .environment(viewModel)
        } else {
            initialStateView
        }
    }
    
    var initialStateView: some View {
        Text("Drop Photo To Get Started")
            .frame(maxWidth: .infinity, maxHeight: .infinity)
            .background(
                isDropAreaTargeted ? .primary : .secondary,
                in: Rectangle(),
                fillStyle: .init()
            )
            .dropDestination(for: Data.self) { items, location in
                guard let data = items.first else { return false }
                
                viewModel.currentImageData = data
                
                return true
            } isTargeted: {
                isDropAreaTargeted = $0
            }
    }
}

#Preview {
    ContentView()
}
