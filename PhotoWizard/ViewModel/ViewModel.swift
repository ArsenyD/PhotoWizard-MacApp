import Foundation

@Observable
class ViewModel {
    var currentImageData: Data? {
        willSet {
            modifiedImageData = newValue
        }
    }
    
    var modifiedImageData: Data?
    var model: Model = Model()
}
