import SwiftUI

struct ImageEditorView: View {
    @Environment(ViewModel.self) var viewModel
    @State private var brightness: Float = 0
    
    var body: some View {
        NavigationSplitView {
            sidebarView
        } detail: {
            imageView()
        }
        
    }
    
    var sidebarView: some View {
        Slider(value: $brightness) {
            Text("Brightness")
        }
        .padding(.horizontal)
    }
    
    private func imageView() -> some View {
        guard let imageData = viewModel.modifiedImageData, let nsImage = NSImage(data: imageData) else { fatalError("Image is nil") }
        
        return Image(nsImage: nsImage)
            .resizable()
            .aspectRatio(contentMode: .fit)
    }
}

#Preview {
    ImageEditorView()
}
