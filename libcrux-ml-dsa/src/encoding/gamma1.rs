use crate::polynomial::PolynomialRingElement;

#[inline(always)]
fn serialize_when_gamma1_is_2_pow_17<const OUTPUT_SIZE: usize>(
    re: PolynomialRingElement,
) -> [u8; OUTPUT_SIZE] {
    let mut serialized = [0u8; OUTPUT_SIZE];
    const GAMMA1: i32 = 1 << 17;

    for (i, coefficients) in re.coefficients.chunks_exact(4).enumerate() {
        let coefficient0 = GAMMA1 - coefficients[0];
        let coefficient1 = GAMMA1 - coefficients[1];
        let coefficient2 = GAMMA1 - coefficients[2];
        let coefficient3 = GAMMA1 - coefficients[3];

        serialized[9 * i] = coefficient0 as u8;
        serialized[9 * i + 1] = (coefficient0 >> 8) as u8;

        serialized[9 * i + 2] = (coefficient0 >> 16) as u8;
        serialized[9 * i + 2] |= (coefficient1 << 2) as u8;

        serialized[9 * i + 3] = (coefficient1 >> 6) as u8;

        serialized[9 * i + 4] = (coefficient1 >> 14) as u8;
        serialized[9 * i + 4] |= (coefficient2 << 4) as u8;

        serialized[9 * i + 5] = (coefficient2 >> 4) as u8;

        serialized[9 * i + 6] = (coefficient2 >> 12) as u8;
        serialized[9 * i + 6] |= (coefficient3 << 6) as u8;

        serialized[9 * i + 7] = (coefficient3 >> 2) as u8;
        serialized[9 * i + 8] = (coefficient3 >> 10) as u8;
    }

    serialized
}

#[inline(always)]
fn serialize_when_gamma1_is_2_pow_19<const OUTPUT_SIZE: usize>(
    re: PolynomialRingElement,
) -> [u8; OUTPUT_SIZE] {
    let mut serialized = [0u8; OUTPUT_SIZE];
    const GAMMA1: i32 = 1 << 19;

    for (i, coefficients) in re.coefficients.chunks_exact(2).enumerate() {
        let coefficient0 = GAMMA1 - coefficients[0];
        let coefficient1 = GAMMA1 - coefficients[1];

        serialized[5 * i] = coefficient0 as u8;
        serialized[5 * i + 1] = (coefficient0 >> 8) as u8;

        serialized[5 * i + 2] = (coefficient0 >> 16) as u8;
        serialized[5 * i + 2] |= (coefficient1 << 4) as u8;

        serialized[5 * i + 3] = (coefficient1 >> 4) as u8;
        serialized[5 * i + 4] = (coefficient1 >> 12) as u8;
    }

    serialized
}

#[inline(always)]
pub(crate) fn serialize<const GAMMA1_EXPONENT: usize, const OUTPUT_SIZE: usize>(
    re: PolynomialRingElement,
) -> [u8; OUTPUT_SIZE] {
    match GAMMA1_EXPONENT {
        17 => serialize_when_gamma1_is_2_pow_17(re),
        19 => serialize_when_gamma1_is_2_pow_19(re),
        _ => unreachable!(),
    }
}

#[inline(always)]
fn deserialize_when_gamma1_is_2_pow_17(serialized: &[u8]) -> PolynomialRingElement {
    const GAMMA1: i32 = 1 << 17;
    const GAMMA1_TIMES_2_BITMASK: i32 = (GAMMA1 << 1) - 1;

    let mut re = PolynomialRingElement::ZERO;

    for (i, bytes) in serialized.chunks_exact(9).enumerate() {
        re.coefficients[4 * i] = bytes[0] as i32;
        re.coefficients[4 * i] |= (bytes[1] as i32) << 8;
        re.coefficients[4 * i] |= (bytes[2] as i32) << 16;
        re.coefficients[4 * i] &= GAMMA1_TIMES_2_BITMASK;

        re.coefficients[4 * i + 1] = (bytes[2] as i32) >> 2;
        re.coefficients[4 * i + 1] |= (bytes[3] as i32) << 6;
        re.coefficients[4 * i + 1] |= (bytes[4] as i32) << 14;
        re.coefficients[4 * i + 1] &= GAMMA1_TIMES_2_BITMASK;

        re.coefficients[4 * i + 2] = (bytes[4] as i32) >> 4;
        re.coefficients[4 * i + 2] |= (bytes[5] as i32) << 4;
        re.coefficients[4 * i + 2] |= (bytes[6] as i32) << 12;
        re.coefficients[4 * i + 2] &= GAMMA1_TIMES_2_BITMASK;

        re.coefficients[4 * i + 3] = (bytes[6] as i32) >> 6;
        re.coefficients[4 * i + 3] |= (bytes[7] as i32) << 2;
        re.coefficients[4 * i + 3] |= (bytes[8] as i32) << 10;
        re.coefficients[4 * i + 3] &= GAMMA1_TIMES_2_BITMASK;

        re.coefficients[4 * i] = GAMMA1 - re.coefficients[4 * i];
        re.coefficients[4 * i + 1] = GAMMA1 - re.coefficients[4 * i + 1];
        re.coefficients[4 * i + 2] = GAMMA1 - re.coefficients[4 * i + 2];
        re.coefficients[4 * i + 3] = GAMMA1 - re.coefficients[4 * i + 3];
    }

    re
}

#[inline(always)]
fn deserialize_when_gamma1_is_2_pow_19(serialized: &[u8]) -> PolynomialRingElement {
    const GAMMA1: i32 = 1 << 19;
    const GAMMA1_TIMES_2_BITMASK: i32 = (GAMMA1 << 1) - 1;

    let mut re = PolynomialRingElement::ZERO;

    for (i, bytes) in serialized.chunks_exact(5).enumerate() {
        re.coefficients[2 * i] = bytes[0] as i32;
        re.coefficients[2 * i] |= (bytes[1] as i32) << 8;
        re.coefficients[2 * i] |= (bytes[2] as i32) << 16;
        re.coefficients[2 * i] &= GAMMA1_TIMES_2_BITMASK;

        re.coefficients[2 * i + 1] = (bytes[2] as i32) >> 4;
        re.coefficients[2 * i + 1] |= (bytes[3] as i32) << 4;
        re.coefficients[2 * i + 1] |= (bytes[4] as i32) << 12;

        re.coefficients[2 * i] = GAMMA1 - re.coefficients[2 * i];
        re.coefficients[2 * i + 1] = GAMMA1 - re.coefficients[2 * i + 1];
    }

    re
}

#[inline(always)]
pub(crate) fn deserialize<const GAMMA1_EXPONENT: usize>(
    serialized: &[u8],
) -> PolynomialRingElement {
    match GAMMA1_EXPONENT {
        17 => deserialize_when_gamma1_is_2_pow_17(serialized),
        19 => deserialize_when_gamma1_is_2_pow_19(serialized),
        _ => unreachable!(),
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_deserialize_when_gamma1_is_2_pow_17() {
        let bytes = [
            198, 32, 33, 79, 53, 132, 46, 198, 17, 233, 84, 94, 175, 136, 13, 127, 137, 254, 113,
            82, 68, 239, 94, 176, 179, 22, 102, 177, 253, 142, 176, 250, 96, 201, 11, 213, 230, 41,
            207, 14, 252, 247, 44, 197, 61, 57, 233, 239, 7, 173, 48, 253, 53, 43, 107, 174, 112,
            33, 144, 137, 117, 234, 75, 181, 150, 72, 158, 193, 130, 225, 136, 17, 65, 227, 146,
            207, 208, 228, 176, 164, 158, 62, 142, 193, 250, 109, 210, 52, 182, 254, 148, 179, 247,
            164, 167, 177, 209, 148, 189, 86, 221, 208, 92, 28, 51, 228, 176, 249, 12, 142, 124,
            187, 37, 164, 131, 203, 222, 228, 211, 250, 222, 114, 123, 183, 44, 125, 14, 97, 12,
            64, 154, 168, 11, 96, 112, 93, 225, 58, 8, 110, 164, 69, 246, 67, 102, 109, 227, 41,
            170, 254, 3, 137, 7, 0, 7, 12, 89, 123, 133, 155, 52, 14, 80, 211, 96, 229, 7, 100,
            208, 68, 109, 222, 122, 84, 80, 163, 240, 121, 126, 235, 54, 72, 124, 163, 195, 30,
            207, 194, 158, 106, 46, 181, 90, 251, 232, 201, 121, 115, 110, 225, 245, 38, 111, 109,
            248, 202, 9, 161, 220, 240, 202, 155, 72, 236, 80, 97, 168, 67, 128, 160, 37, 56, 211,
            167, 71, 73, 215, 92, 101, 148, 227, 207, 180, 155, 233, 42, 144, 30, 28, 236, 184, 13,
            133, 206, 47, 170, 205, 59, 29, 209, 245, 226, 66, 69, 144, 146, 168, 83, 66, 233, 193,
            59, 79, 41, 167, 246, 246, 95, 161, 50, 105, 109, 255, 137, 188, 210, 189, 142, 91, 73,
            139, 24, 228, 30, 36, 133, 202, 123, 206, 244, 9, 229, 227, 255, 94, 198, 149, 5, 193,
            37, 72, 129, 16, 205, 245, 177, 242, 241, 120, 66, 137, 39, 20, 111, 197, 64, 89, 9,
            238, 114, 4, 212, 146, 75, 206, 58, 232, 33, 231, 186, 90, 202, 95, 49, 233, 209, 177,
            195, 88, 253, 80, 103, 112, 163, 245, 31, 6, 78, 119, 131, 17, 240, 77, 210, 72, 61, 1,
            104, 110, 70, 49, 83, 172, 187, 39, 53, 235, 40, 4, 19, 170, 110, 153, 249, 52, 6, 122,
            225, 235, 40, 196, 149, 80, 184, 69, 148, 61, 158, 255, 145, 72, 129, 51, 16, 2, 196,
            156, 146, 128, 107, 76, 122, 194, 42, 99, 240, 12, 213, 57, 55, 232, 145, 61, 45, 160,
            136, 168, 6, 128, 210, 250, 114, 174, 126, 230, 8, 228, 207, 143, 146, 135, 161, 201,
            156, 182, 241, 219, 217, 69, 27, 35, 156, 194, 91, 192, 115, 201, 22, 197, 145, 240,
            132, 11, 206, 138, 128, 139, 222, 212, 13, 212, 22, 92, 232, 216, 16, 69, 109, 55, 230,
            217, 210, 95, 192, 242, 193, 250, 91, 217, 140, 11, 98, 111, 8, 117, 91, 212, 63, 24,
            93, 161, 48, 241, 55, 11, 5, 171, 199, 212, 161, 230, 156, 205, 103, 171, 11, 226, 125,
            213, 216, 76, 17, 229, 56, 203, 30, 43, 39, 212, 232, 96, 198, 217, 109, 81, 125, 22,
            180, 195, 249, 20, 18, 57, 153, 132, 63, 206, 40, 137, 240, 149, 189, 220, 75, 227,
            142, 178, 214, 215, 101, 232, 204, 94, 189, 109, 236, 173, 200, 39, 114, 203, 136, 152,
            114, 173, 199, 38, 195, 46, 224, 68, 92, 129, 184, 157, 35,
        ];

        let expected_coefficients = [
            57146, 44088, -59459, 112872, -21737, -11223, -127192, -129573, 109967, -113617,
            -80645, 26534, -64945, -44067, 92657, -87087, -76262, -66483, -53119, 67820, -125241,
            -82427, -119562, 86825, 86421, 128932, -88217, 53335, 92491, 104558, -6188, 113117,
            -58177, 117788, -69197, -31378, 29122, -97968, -85286, -129752, -111508, 5827, 58598,
            -63059, 74410, -71476, -17201, -124611, 94708, 37153, 116158, -97070, -54244, 84034,
            -96183, 2894, 106226, -36867, 83319, 16000, -57693, -98830, 107962, 61479, -93542,
            -35448, 114710, 123356, 129280, -54851, 18345, 116526, 76976, 1704, 63936, 19181,
            99618, 76779, -106250, -110073, 112586, 71457, 69140, -31499, 53654, -54957, 90481,
            12825, 7826, -117181, -100054, 121045, 74591, -62140, -50313, 31421, 113752, 38880,
            52350, 57697, 75959, 59049, 65991, -28371, 120087, -67492, -102081, -5174, -12238,
            -62314, 60973, -101335, 113342, -9380, 121542, -67493, 45253, 22070, 145, 79227,
            -93545, -74367, -122155, 37318, 95415, -112902, 110015, 4310, 2866, 67262, 4098,
            -22297, 16123, 110071, 77560, -51159, 69134, -20638, 48520, -71100, 42688, 83070,
            49081, 53685, 116018, 14214, 21586, 32983, 5839, 70540, -120204, 25277, 23696, 30723,
            -95456, 113139, -19952, -86580, -32787, 58951, 109775, 4373, -45906, 126813, -43539,
            -26203, 105649, -99816, 120597, 121487, 107643, 68015, 98, 110044, 64712, -69640,
            93540, -72416, 120924, 29525, 62224, 12683, 57725, 84746, 96096, 130646, -109864,
            -47563, 72066, -129282, 55044, -34334, -40137, -64621, 107107, 95123, -115356, 69610,
            37737, -18196, -99568, -45954, 83960, -86906, -54285, -5893, 62066, 19180, 6601,
            -128182, -76805, -125703, 75429, 97565, 96522, 37420, 114732, 108730, -70410, 119585,
            -109317, 101071, 12694, 24778, -2987, 41096, 78451, -103493, -52024, 13625, -36162,
            -72067, 37415, 24748, 115903, 109593, 50926, -123174, -36067, -115236, 82539, 77065,
            -76014, -89946, 71579, -87987, -50907, -74423, -94759, -8754, -55081, 91362, 119101,
            -69944, -100373, 94602,
        ];

        assert_eq!(
            deserialize::<17>(&bytes).coefficients,
            expected_coefficients
        );
    }

    #[test]
    fn test_deserialize_when_gamma1_is_2_pow_19() {
        let bytes: [u8; 640] = [
            253, 11, 216, 60, 251, 71, 79, 187, 242, 250, 209, 44, 72, 206, 98, 3, 22, 91, 184, 22,
            197, 50, 249, 184, 253, 104, 8, 3, 9, 116, 147, 157, 110, 167, 67, 218, 30, 79, 58, 12,
            2, 72, 239, 104, 6, 162, 57, 195, 128, 18, 93, 245, 0, 132, 218, 172, 178, 214, 243,
            53, 171, 128, 90, 13, 126, 226, 148, 153, 238, 106, 146, 46, 220, 184, 140, 28, 167,
            18, 38, 212, 17, 6, 136, 251, 94, 47, 164, 196, 66, 120, 204, 45, 111, 37, 45, 51, 38,
            109, 32, 32, 144, 122, 13, 52, 144, 108, 75, 152, 73, 164, 139, 91, 26, 37, 76, 237,
            211, 47, 124, 0, 210, 175, 145, 149, 28, 19, 81, 38, 3, 121, 106, 191, 144, 129, 93,
            118, 202, 8, 163, 27, 182, 42, 148, 249, 166, 67, 198, 69, 164, 49, 157, 40, 230, 39,
            126, 108, 93, 96, 211, 185, 61, 99, 30, 83, 183, 241, 30, 16, 91, 76, 200, 55, 228, 22,
            33, 142, 114, 240, 217, 138, 155, 223, 136, 77, 216, 181, 102, 56, 218, 49, 91, 223,
            67, 68, 190, 216, 214, 180, 230, 199, 165, 17, 171, 151, 156, 33, 125, 248, 0, 56, 104,
            184, 150, 91, 83, 138, 61, 162, 255, 96, 168, 189, 86, 60, 76, 36, 163, 207, 76, 227,
            76, 180, 145, 125, 229, 251, 212, 77, 115, 88, 177, 134, 20, 122, 27, 211, 207, 254,
            233, 226, 31, 112, 10, 181, 117, 97, 56, 188, 176, 229, 156, 140, 97, 31, 64, 139, 249,
            217, 172, 100, 70, 121, 130, 94, 182, 245, 239, 138, 4, 65, 64, 228, 118, 200, 128, 94,
            143, 59, 53, 12, 185, 209, 191, 52, 91, 170, 161, 200, 12, 223, 221, 54, 151, 218, 3,
            156, 49, 176, 78, 50, 117, 16, 36, 179, 203, 91, 222, 181, 53, 151, 211, 229, 22, 49,
            247, 223, 195, 241, 1, 44, 157, 56, 48, 158, 25, 246, 231, 54, 106, 197, 107, 199, 252,
            60, 182, 216, 27, 129, 32, 149, 8, 239, 44, 176, 119, 104, 207, 77, 206, 150, 220, 18,
            172, 54, 140, 37, 235, 243, 23, 220, 149, 241, 197, 149, 240, 41, 223, 179, 98, 188,
            135, 231, 56, 176, 102, 173, 39, 46, 236, 79, 177, 224, 17, 164, 88, 227, 108, 214,
            234, 106, 253, 242, 27, 120, 44, 44, 63, 117, 135, 97, 90, 239, 81, 138, 112, 203, 188,
            13, 239, 224, 37, 53, 1, 27, 33, 26, 213, 36, 129, 146, 254, 82, 106, 111, 179, 25,
            199, 217, 243, 188, 250, 141, 136, 148, 154, 241, 152, 195, 225, 82, 174, 149, 124,
            237, 3, 81, 218, 90, 157, 6, 243, 34, 62, 141, 211, 164, 2, 103, 45, 46, 253, 115, 244,
            216, 191, 245, 177, 121, 216, 86, 131, 66, 63, 18, 167, 41, 199, 241, 195, 117, 168,
            134, 193, 73, 201, 83, 197, 85, 147, 217, 45, 162, 18, 203, 166, 95, 166, 159, 8, 1,
            110, 125, 113, 228, 180, 78, 194, 174, 60, 172, 124, 151, 23, 202, 247, 189, 206, 204,
            101, 51, 35, 8, 196, 85, 237, 64, 222, 81, 143, 182, 205, 105, 110, 173, 197, 239, 196,
            5, 108, 128, 248, 191, 247, 43, 25, 180, 246, 154, 125, 142, 227, 246, 17, 2, 207, 193,
            89, 244, 159, 82, 218, 117, 78, 191, 40, 49, 154, 160, 83, 246, 93, 94, 52, 85, 45,
            140, 99, 40, 23, 179, 141, 10, 143, 62, 176, 84, 19, 94, 79, 72, 58, 138, 7, 87, 196,
            2, 87, 0, 191, 226, 2, 224, 187, 150, 199, 217, 211, 51, 114, 228, 71, 54, 23, 17, 9,
            212, 195, 125, 236, 213, 254, 189, 203, 232, 161, 50, 81, 174, 129, 117,
        ];

        let expected_coefficients = [
            -3069, -504781, -216903, -503595, -11473, 119580, -202243, 431227, -78533, -514959,
            325528, 49008, -433555, 247178, -466650, 474204, -477186, 498034, 312926, 448500,
            461475, -370752, 85332, 303299, -164011, 7979, -103650, 86295, -274066, -52109, 350436,
            -344673, -1553, 135240, 220113, 31700, -470476, 339370, -337459, 392698, -359056,
            -66368, -19308, -148633, -154507, 212399, -513005, 522302, 413742, 407207, 110317,
            28622, 475286, 141287, -51830, 411088, 251210, -159641, 145853, 320956, 120675, 7554,
            500372, -236854, -418621, -226609, 516367, 211535, 247864, 388754, 494962, -44447,
            -57243, -361688, -26293, 320093, 270501, -255044, 207144, -294507, -201125, -117114,
            -32033, 294897, 83864, 182855, 377462, 126982, 82520, 212027, -500516, -406732, 412596,
            -415705, -382203, 161996, 227663, 411743, -446419, -405151, -159775, 42160, -276577,
            -416523, 422756, 261642, -129419, 111923, 362170, -222696, -192501, 257976, 72640,
            -3207, -233310, 474285, -512441, 150709, -41386, -389324, 51491, 508503, 511588,
            318229, 257931, -310066, 139685, -95067, 72237, -488209, 408609, 344033, 509795,
            419357, 71690, -284323, -313195, -222159, 451624, -86536, -323336, 34046, -380776,
            -93412, -266972, -50026, 267483, -377215, 134763, -461148, 270551, -247339, -59271,
            103677, -403373, 196926, 401231, 161215, 103197, 86355, -258813, 342143, 180436,
            124809, 397478, 63323, -376011, -397040, 445147, 388688, 207590, -75794, -152318,
            -210678, -116505, -249661, -36346, -108872, 288527, 184804, -300462, 508201, -186961,
            497195, -402163, -342227, 64860, 335146, 232451, -261519, -111093, 168569, -475779,
            -160035, 407767, 41921, 424280, -300188, 146093, -366901, 351699, -158897, -501343,
            520055, 426642, -216647, -442958, -181194, 26756, -490657, -315069, 313764, 260061,
            -447836, 401856, -223477, -420301, -285398, 146193, -1728, 16392, 421185, -194228,
            -59353, 395549, -323617, 239167, 185857, -423386, 357388, 484815, -484666, 237987,
            338605, -25484, -209266, -461453, -197608, -398164, 228107, 30150, -279920, 502014,
            -404464, -253954, -293227, 273447, -411427, 51641, 487151, -377812, -351943, -245246,
            -138892, -414002, 42982,
        ];

        assert_eq!(
            deserialize::<19>(&bytes).coefficients,
            expected_coefficients
        );
    }
}
