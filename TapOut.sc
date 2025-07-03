TapOut : UGen {
	*ar { |sig|

		^this.multiNew('audio',*sig)

	}

}
