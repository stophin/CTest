package com.nano.ctest;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.nano.swig.CTest;
import com.nano.swig.NanoJNI;
import com.nano.swig.NanoJNIJNI;
import com.nano.swig.SWIGTYPE_p_CTest;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.text.TextUtils;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.SearchView;
import android.widget.SimpleAdapter;
import android.widget.TextView;

public class MainActivity extends Activity {
	static {
		System.loadLibrary("NanoJNI");
	}
	
	private ListView listView;
	private SearchView searchView;
	private TextView detailView;
	private TextView mainRes;
	
	private ProgressDialog progressDialog = null;
	
	public void showProgressDialog(String title, String message) {
		if (progressDialog == null) {
			progressDialog = ProgressDialog.show(MainActivity.this, title, message, true, false);
		} else if (progressDialog.isShowing()) {
			progressDialog.setTitle(title);
			progressDialog.setMessage(message);
		}
		progressDialog.show();
	}
	
	public void hideProgressDialog() {
		if (progressDialog != null && progressDialog.isShowing()) {
			progressDialog.dismiss();
		}
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		listView = (ListView)findViewById(R.id.listView);
		searchView = (SearchView)findViewById(R.id.searchView);
		detailView = (TextView)findViewById(R.id.mainView);
		mainRes = (TextView)findViewById(R.id.mainRes);
		
		
		
		NanoJNIJNI.Start();
		
		final Handler handler = new Handler() {
			public void handleMessage(Message msg) {
				int count = msg.getData().getInt("count");
				if (count > 0) {
					detailView.setText("正在加载(" + count + ")");
				} else {
					detailView.setText(String.valueOf(-count) + "词汇");
				}
			}
		};
		
 		new Thread() {
 			public void run() {
				//从文件中读取数据
		        InputStream is = null;
		 		int count = 0;
		        try {
		        	is=MainActivity.this.getResources().openRawResource(R.raw.cet6);
		        	InputStreamReader ir = new InputStreamReader(is, "UTF-8");
			 		
			 		 BufferedReader buffreader = new BufferedReader(ir);
			 		 String result;
				     while((result = buffreader.readLine()) != null) {
				    	 if (NanoJNIJNI.Iterator(result) == 0) {
				    		 break;
				    	 }
				    	 if (count ++ % 100 == 0) {
					    	 Message msg = new Message();
					    	 Bundle bundle = new Bundle();
					    	 bundle.putInt("count", count++);
					    	 msg.setData(bundle);
					    	 handler.sendMessage(msg);
				    	 }
				     }
		        } catch(Exception e) {
		        	
		        } finally{
			    	 Message msg = new Message();
			    	 Bundle bundle = new Bundle();
			    	 bundle.putInt("count", -count);
			    	 msg.setData(bundle);
			    	 handler.sendMessage(msg);
					if(is!=null){
						try {
							is.close();
						} catch (IOException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
					}
				}
 			}
 		}.start();
        
        searchView.setOnQueryTextListener(new SearchView.OnQueryTextListener() {
			
			@Override
			public boolean onQueryTextSubmit(String query) {
				// TODO Auto-generated method stub
				int i;
				int count = NanoJNIJNI.Search(query);
			    mainRes.setText(String.valueOf(count) + "/");
				if (count <= 0) {
					return false;
				}
				searchView.clearFocus();
			     String result = NanoJNIJNI.Result();
			     final String[] list = result.split("-->");
			     List<Map<String, Object>> records = new ArrayList<Map<String, Object>>();
			     for (i = 0; i < list.length; i++) {
			    	 Map<String, Object> map = new HashMap<String, Object>();
			    	 String[] temp = list[i].split("->");
			    	 map.put("list", temp[0]);
			    	 map.put("trans", adapterTrans( temp[1]));
			    	 records.add(map);
			     }
			     
			     SimpleAdapter adapter = new SimpleAdapter(MainActivity.this, records,
			             android.R.layout.simple_list_item_2, new String[] { "list",
			                     "trans" }, new int[] { android.R.id.text1,
			    		 			android.R.id.text2});
			    // TextView tv2 = (TextView)findViewById(android.R.id.list_textView2);
			    // tv2.setEllipsize(TextUtils.TruncateAt.valueOf("END"));
			     
			     listView.setAdapter(adapter);
			     /*
			     
			     listView.setAdapter(new ArrayAdapter<String>(MainActivity.this,
					android.R.layout.simple_list_item_2, list));
			     */

			     listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {

						@Override
						public void onItemClick(AdapterView<?> parent, View view,
								int position, long id) {
							// TODO Auto-generated method stub
							switch(parent.getId()) {
							case R.id.listView:
								Bundle bundle = new Bundle();

							    String trans = NanoJNIJNI.Result_Trans(position);
							    String examp = NanoJNIJNI.Result_Examp(position);
								bundle.putString("res", list[position].split("->")[0]);
								bundle.putString("trans", trans);
								bundle.putString("examp", examp);
								
								Intent intent = new Intent(MainActivity.this, DetailActivity.class);
								intent.putExtras(bundle);
								startActivity(intent);
								overridePendingTransition(android.R.anim.slide_in_left,android.R.anim.slide_out_right);
							}
						}
						
					});
				return true;
			}
			
			@Override
			public boolean onQueryTextChange(String newText) {
				// TODO Auto-generated method stub
				if (newText == null || newText.isEmpty()) {
					String[] list = {};
				     listView.setAdapter(new ArrayAdapter<String>(MainActivity.this,
								android.R.layout.simple_list_item_single_choice, list));
					return true;
				}
				return false;
			}
		});
	     
        /*
        TextView tv = new TextView(this);
        InputStream is = null;
        try {
     		String result = NanoJNIJNI.Start();
	        tv.setText(String.valueOf(NanoJNI.getuid()) + ":" + result);
	        
     		is=this.getResources().openRawResource(R.raw.test);
     		InputStreamReader ir = new InputStreamReader(is, "UTF-8");
     		
     		DataInputStream ds = new DataInputStream(is);
	        while((result = ds.readLine()) != null) {
	        	NanoJNIJNI.Iterator(result);
	        }
     		 BufferedReader buffreader = new BufferedReader(ir);
 	        while((result = buffreader.readLine()) != null) {
 	        	NanoJNIJNI.Iterator(result);
 	        }
	        
	        
	        result = NanoJNIJNI.Result();
	        tv.setText(String.valueOf(NanoJNI.getuid()) + ":" + result);

       }catch(Exception e){ 
          e.printStackTrace();         
       } finally{
			if(is!=null){
				try {
					is.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}	
       this.setContentView(tv);*/
	}
    
    private String adapterTrans(String trans) {/*
    	trans = trans.replace("\n", " ");
    	return trans.length() > 30 ? trans.substring(0, 30) + "..." : trans;*/
    	return trans.replace("\n",  " ");
    }

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
}
