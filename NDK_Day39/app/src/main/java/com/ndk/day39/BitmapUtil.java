package com.ndk.day39;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

public class BitmapUtil {
    public static Bitmap gray(Bitmap src) {
        Bitmap dst = Bitmap.createBitmap(src.getWidth(), src.getHeight(), src.getConfig());
        //Java 像素操作
        int[] pixels = new int[src.getWidth() * src.getHeight()];
        /*让我们逐个参数解释：
@NonNull @ColorInt int[] pixels:
这是一个输出参数，表示一个整型数组，用于接收从 Bitmap 中复制出来的像素颜色数据。
@NonNull 注解表示这个数组不能为空。
@ColorInt 注解表示数组中的每个整型值代表一个颜色。
这个数组的大小必须足够容纳要复制的所有像素数据。
int offset:
指定从 pixels 数组的哪个索引开始写入像素数据。
例如，如果 offset 是 0，数据将从数组的第一个元素开始写入。
int stride:
表示在 pixels 数组中，两行像素数据之间的间隔（以整型元素的数量为单位） 。
这个参数允许你在 pixels 数组中为每行像素数据之间留出空白。
对于通常的紧密排列的像素数据，stride 的值应该等于你要读取的 width。
stride 的值必须大于或等于要读取的 width 的绝对值 (abs(stride) >= width)。stride 也可以是负数，这会改变行的存储顺序。
int x:
指定要从 Bitmap 中开始读取像素数据的区域的左上角的 x 坐标（列索引）。
范围是 0 到 Bitmap 的宽度减 1。
int y:
指定要从 Bitmap 中开始读取像素数据的区域的左上角的 y 坐标（行索引）。
范围是 0 到 Bitmap 的高度减 1。
int width:
指定要从 Bitmap 中读取的每行的像素数量。
必须是非负数。
int height:
指定要从 Bitmap 中读取的行数。
必须是非负数。
返回的颜色格式
getPixels() 方法返回的颜色是非预乘的 ARGB 值。
这些颜色值位于 ColorSpace.Named.SRGB sRGB 颜色空间中。
*/
        src.getPixels(pixels, 0, src.getWidth(), 0, 0, src.getWidth(), src.getHeight());
           /*这段代码的目的是从一个代表像素颜色的整型值 p 中提取出它的 ARGB（透明度、红、绿、蓝）四个颜色分量。
        p 是一个 32 位的整型数，它按照 ARGB 的顺序存储了这四个分量的值，每个分量占用 8 位（一个字节）。其结构大致如下：*/
    /*31 30 ... 24 | 23 22 ... 16 | 15 14 ...  8 |  7  6 ...  0
   ----------------------------------------------------------
    透明度 (A)   |      红色 (R)    |     绿色 (G)    |     蓝色 (B)*/

/*位运算的作用
这里的位运算主要使用了右移 (>>) 和按位与 (&) 操作符，它们的目的是：
将感兴趣的颜色分量移动到最低 8 位：通过右移操作，我们将目标颜色分量移动到整型数的最低 8 位，这样方便后续提取。
使用按位与 (& 0xff) 屏蔽掉高位的其他分量：0xff 在二进制中表示为 00000000 ... 00000000 11111111（前 24 位为 0，后 8 位为 1）。将右移后的结果与 0xff 进行按位与操作，可以保留最低 8 位的值，同时将高于 8 位的其他位清零。这样就只剩下我们想要提取的那个颜色分量的值了。 */

        /*int a = (p >> 24) & 0xff;
            p >> 24: 将整型数 p 向右移动 24 位。这将把透明度（A）分量移动到最低 8 位。
            原始的 p： [A][R][G][B]
            右移 24 位后： [0][0][0][A] (高位用 0 填充)
            & 0xff: 将右移后的结果与 0xff 进行按位与操作。
            [0][0][0][A] & [0][0][0][FF] = [0][0][0][A]
            结果：提取出透明度分量 a，其值范围为 0 到 255。*/

        /*int r = (p >> 16) & 0xff;
            p >> 16: 将整型数 p 向右移动 16 位。这将把红色（R）分量移动到最低 8 位。
            原始的 p： [A][R][G][B]
            右移 16 位后： [0][0][A][R]
            & 0xff: 将右移后的结果与 0xff 进行按位与操作。
            [0][0][A][R] & [0][0][0][FF] = [0][0][0][R]
            结果：提取出红色分量 r，其值范围为 0 到 255。
        * */
        for (int i = 0; i < pixels.length; i++) {
            int p = pixels[i];
            int a = (p >> 24) & 0xff;
            int r = (p >> 16) & 0xff;
            int g = (p >> 8) & 0xff;
            int b = (p) & 0xff;

            int gray = (int) (0.3 * r + 0.59 * g + 0.11 * b);
            /*这行代码的作用是将计算得到的灰度值 gray 和原始的透明度 a 重新组合成一个 32 位的整型颜色值，并存回 pixels 数组中，用于替换原始像素的颜色。 我们来逐个解释位运算操作：
             */

            /*
            a << 24:
a 是原始像素的透明度分量，取值范围是 0 到 255。
<< 24 是左移操作，将 a 的值向左移动 24 位。
这会将 a 的值移动到整型数的最高 8 位，也就是透明度（A）分量的位置。
例如，如果 a = 0xff (255)，那么 a << 24 的结果就是 0xff000000。
gray << 16:
gray 是你计算得到的灰度值，取值范围也是 0 到 255。
<< 16 是左移操作，将 gray 的值向左移动 16 位。
这会将 gray 的值移动到红色（R）分量的位置。
例如，如果 gray = 0x80 (128)，那么 gray << 16 的结果就是 0x00800000。
gray << 8:
gray 是你计算得到的灰度值。
<< 8 是左移操作，将 gray 的值向左移动 8 位。
这会将 gray 的值移动到绿色（G）分量的位置。
例如，如果 gray = 0x80，那么 gray << 8 的结果就是 0x00008000。
gray:
灰度值 gray 本身就代表了蓝色（B）分量的值，因为它将直接放在最低 8 位。
例如，如果 gray = 0x80，那么它在最低 8 位就是 0x00000080。
| (按位或):
按位或操作符用于将前面左移操作得到的结果进行组合。
由于不同的颜色分量被移动到了不同的位段， 它们之间的位是不会重叠的， 所以使用按位或可以将它们“ 合并” 到一个整型数中。
            * */

            /*例如：
            * (a << 24):    [A][0][0][0]
        (gray << 16): [0][gray][0][0]
        (gray << 8):  [0][0][gray][0]
        (gray):       [0][0][0][gray]
        -----------------------------
        按位或结果:   [A][gray][gray][gray]*/
            pixels[i]= (a << 24) | (gray << 16) | (gray << 8) | gray;

        }

        //将像素点设置回去
        dst.setPixels(pixels, 0, dst.getWidth(), 0, 0, dst.getWidth(), dst.getHeight());

        //直接修改原图
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inMutable = true;

        return dst;
    }
}
