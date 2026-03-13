import Foundation

protocol PhotoEditorProtocol {
    func increaseBrightness(completionHandler: (Data) -> Void)
}
