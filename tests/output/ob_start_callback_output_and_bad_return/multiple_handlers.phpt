--TEST--
ob_start(): Check behaviour with multiple nested handlers with bad return values and output
--FILE--
<?php

$log = [];

function return_given_string($string) {
    global $log;
    $log[] = __FUNCTION__ . ": <<<" . $string . ">>>";
    echo __FUNCTION__;
    return $string;
}

function return_empty_string($string) {
    global $log;
    $log[] = __FUNCTION__ . ": <<<" . $string . ">>>";
    echo __FUNCTION__;
    return "";
}

function return_false($string) {
    global $log;
    $log[] = __FUNCTION__ . ": <<<" . $string . ">>>";
    echo __FUNCTION__;
    return false;
}

function return_true($string) {
    global $log;
    $log[] = __FUNCTION__ . ": <<<" . $string . ">>>";
    echo __FUNCTION__;
    return true;
}

function return_null($string) {
    global $log;
    $log[] = __FUNCTION__ . ": <<<" . $string . ">>>";
    echo __FUNCTION__;
    return null;
}

function return_string($string) {
    global $log;
    $log[] = __FUNCTION__ . ": <<<" . $string . ">>>";
    echo __FUNCTION__;
    return "I stole your output.";
}

function return_zero($string) {
    global $log;
    $log[] = __FUNCTION__ . ": <<<" . $string . ">>>";
    echo __FUNCTION__;
    return 0;
}

ob_start('return_given_string');
ob_start('return_empty_string');
ob_start('return_false');
ob_start('return_true');
ob_start('return_null');
ob_start('return_string');
ob_start('return_zero');

echo "Testing...";

ob_end_flush();
ob_end_flush();
ob_end_flush();
ob_end_flush();
ob_end_flush();
ob_end_flush();
ob_end_flush();

echo "\n\nLog:\n";
echo implode("\n", $log);
?>
--EXPECTF--
Deprecated: ob_end_flush(): Producing output from user output handler return_given_string is deprecated in %s on line %d0

Deprecated: ob_end_flush(): Producing output from user output handler return_empty_string is deprecated in %s on line %d9


Log:
return_zero: <<<Testing...>>>
return_string: <<<
Deprecated: ob_end_flush(): Producing output from user output handler return_zero is deprecated in %s on line %d

Deprecated: ob_end_flush(): Returning a non-string result from user output handler return_zero is deprecated in %s on line %d
0>>>
return_null: <<<
Deprecated: ob_end_flush(): Producing output from user output handler return_string is deprecated in %s on line %d5
I stole your output.>>>
return_true: <<<
Deprecated: ob_end_flush(): Producing output from user output handler return_null is deprecated in %s on line %d

Deprecated: ob_end_flush(): Returning a non-string result from user output handler return_null is deprecated in %s on line %d
>>>
return_false: <<<
Deprecated: ob_end_flush(): Producing output from user output handler return_true is deprecated in %s on line %d

Deprecated: ob_end_flush(): Returning a non-string result from user output handler return_true is deprecated in %s on line %d
>>>
return_empty_string: <<<
Deprecated: ob_end_flush(): Producing output from user output handler return_false is deprecated in %s on line %d

Deprecated: ob_end_flush(): Returning a non-string result from user output handler return_false is deprecated in %s on line %d

Deprecated: ob_end_flush(): Producing output from user output handler return_true is deprecated in %s on line %d

Deprecated: ob_end_flush(): Returning a non-string result from user output handler return_true is deprecated in %s on line %d
return_false>>>
return_given_string: <<<
Deprecated: ob_end_flush(): Producing output from user output handler return_empty_string is deprecated in %s on line %d9
>>>
