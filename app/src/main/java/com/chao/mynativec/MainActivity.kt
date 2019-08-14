package com.chao.mynativec

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.text.Html
import android.util.Log
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    @SuppressLint("SetTextI18n")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
        val array = intArrayOf(5,2,55,66,7,888,0,77,2,55555,2,-4,85)
        val low = getLowest(array)
        val log = "lowest of array is $low"
        Log.d(TAG,log)

        val stringBuffer = StringBuffer("selectionSort:")
        selectionSort(array).forEach {
            stringBuffer.append("$it ,")
        }
        stringBuffer.append("<br/> jni sort :")
        sort(array).forEach {
            stringBuffer.append("$it ,")
        }

        sample_text.text = Html.fromHtml("$log <br/> ${stringFromJNI()} <br/> $stringBuffer")
    }

    /**
     * 选择排序
     */
    private fun selectionSort(a: IntArray):IntArray{
        Log.d(TAG,"size = ${a.size}")
        return if (a.size < 2){
            a
        }else {
            val stand = a.first()

            val b = ArrayList<Int>()
            val c = ArrayList<Int>()

            a.forEachIndexed { index, it ->
                when {
                    it > stand -> b.add(it)
                    index == 0 ->{ }
                    else -> c.add(it)
                }
            }
            selectionSort(c.toIntArray()) + stand + selectionSort(b.toIntArray())
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    private external fun stringFromJNI(): String

    private external fun getLowest(a: IntArray): Int

    private external fun sort(a: IntArray): IntArray

    companion object {

        const val TAG = "MainActivity"
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}
