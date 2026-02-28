import Cocoa

class ViewController: NSViewController {
    override func viewDidLoad() {
        super.viewDidLoad()
        view.window?.contentView?.window?.backgroundColor = .red
    }

    override var representedObject: Any? {
        didSet {}
    }
}
