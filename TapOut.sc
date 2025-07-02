TapOut : UGen {
    *ar { |in|
        var inArray = in.asArray;
        ^this.multiNewList('audio', inArray)
    }
}
