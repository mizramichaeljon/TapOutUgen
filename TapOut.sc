TapOut : UGen {
    *ar { |in|
        ^this.multiNew('audio', in)
    }

    init { |...args|
        ^super.init(*args)
    }
}