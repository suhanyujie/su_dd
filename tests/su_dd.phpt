--TEST--
Test su_dd's function:
su_test
su_test_reverse

--SKIPIF--
<?php
printf("%.2f\n", su_test(62));
printf("%.2f", su_test_reverse(62));
?>
--EXPECTF--
16.67
143.60
